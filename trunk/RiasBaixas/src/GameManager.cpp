#include <ngl/Obj.h>
//glew must be included first!
#include <iostream>
#include <ngl/VAOPrimitives.h>
#include <ngl/TransformStack.h>
#include "Renderer.h"
#include "SourceManager.h"
#include "CameraManager.h"
#include "SpeedBoat.h"
#include "Sea.h"
#include "Object.h"
#include "ObjectManager.h"
#include "Controller.h"
#include "PlayerControls.h"
#include "Floating.h"
#include "TXTParser.h"
#include "Diagonal.h"
#include "Floating.h"
#include "Horizontal.h"
#include "Vertical.h"
#include "PhysicsEngine.h"
#include "BSpherePE.h"
#include "Utilities.h"

int main()
{

    static const int GAMEMANAGER_FPS = 30;

    //NEEDED OBJECTS
    Renderer myRenderer;
    SourceManager mySourceManager;
    ObjectManager myObjectManager;
    ControllerManager myControllerManager;
    CameraManager myCameraManager;
    playerOptions myPlayerOptions;
    Utilities myUtilities;

    myRenderer.initGLContext();

    //Loading models
    //Eventually this will be loaded by the parser automatically
    mySourceManager.addMesh("helix", new ngl::Obj("models/Helix.obj"));
    mySourceManager.addMesh("spaceship", new ngl::Obj("models/SpaceShip.obj"));
    mySourceManager.addMesh("speedboat", new ngl::Obj("models/speedboat.obj","textures/speedboat.jpg"));
    mySourceManager.addMesh("sea", new ngl::Obj("models/sea.obj","textures/sea.png"));
    mySourceManager.addMesh("musselFarm", new ngl::Obj("models/musselFarm.obj","textures/musselFarm.jpg"));
    mySourceManager.addMesh("fisherBoat", new ngl::Obj("models/fisherBoat.obj","textures/fisherBoat.jpg"));

    //LOADING THE MAIN CHARACTER: THE SPEEDBOAT
    SpeedBoat* mySpeedBoat = new SpeedBoat();
    PlayerControls* myPlayerControls = new PlayerControls();
    myPlayerControls->setControlledObject(mySpeedBoat);
    mySpeedBoat->setMesh(mySourceManager.getMesh("speedboat"));
    //mySpeedBoat.setScale(ngl::Vec4(0.2,0.2,0.2,1));
    //mySpeedBoat.setRotation(ngl::Vec4(0,-90,0,1));
    myObjectManager.addObject(mySpeedBoat);
    myControllerManager.addController(myPlayerControls);
    myObjectManager.setCentralObject(mySpeedBoat);
    myObjectManager.setFar(myCameraManager.getFar());

    //LOADING MAP
    Parser *myParser = new TXTParser();
    myParser->loadLevelSources(0, mySourceManager);
    myParser->loadMap(0, myObjectManager, myControllerManager, mySourceManager);

    //Loading and linking cameras
    myCameraManager.loadCameras(myRenderer.getWindowWidth(),myRenderer.getWindowHeight());
    myCameraManager.setTarget(mySpeedBoat);

    //PHYSICS ENGINE
    PhysicsEngine *myPhysicsEngine = new BSpherePE();

    //TIMING
    Uint32 startingTick;
    int frameCounter = 0;
    Uint32 lastStartingSecond = SDL_GetTicks();
    int fps;


    //GAME LOOP
    while (myPlayerOptions.running)
    {
        startingTick = SDL_GetTicks();

        myUtilities.readPlayerInput(*myPlayerControls, myPlayerOptions, myRenderer.isFullScreen());

        myUtilities.setWindow(myRenderer,myPlayerOptions);
        myUtilities.setCamera(myCameraManager, myRenderer, myPlayerOptions);

        if (!myPlayerOptions.pause)
        {
            myObjectManager.checkActiveObjects();
            myControllerManager.updateControllers();
            myObjectManager.checkCollisions(myPhysicsEngine);

            myCameraManager.updateCameras();

            myRenderer.render(myObjectManager.sea(),myObjectManager.objects(),*myCameraManager.getCurrentCamera(),myPlayerOptions.debugMode);
        }

        myUtilities.regulateFPS(startingTick, frameCounter, lastStartingSecond, fps, GAMEMANAGER_FPS);

        std::cout << "WORKING AT "<< fps <<" FPS" << std::endl;

        //std::cout << "GAMEMANAGER: DISTANCE TO THE BEACH: " << (SEA_DEPTH+mySpeedBoat.getPosition().m_z) << std::endl;

        //std::cin.ignore();
    }
    return 0;
}






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
#include "MusselFarm.h"
#include "Controller.h"
#include "PlayerControls.h"
#include "Floating.h"
#include "TxtParser.h"
#include "Diagonal.h"


struct playerOptions
{
    bool running = true;
    int debugMode = 0;
    bool backCamera = false;
    bool changeCamera = false;
};

void readPlayerInput(PlayerControls &_playerControls, playerOptions &_playerOptions);
void setCamera(ngl::Camera *&_cam, CameraManager &_cameraManager, playerOptions &_playerOptions);

int main()
{

    //NEEDED OBJECTS
    Renderer myRenderer;
    SourceManager mySourceManager;
    ObjectManager myObjectManager;
    CameraManager myCameraManager;
    PlayerControls myPlayerControls;
    playerOptions myPlayerOptions;

    myRenderer.initGLContext();

    //Loading models
    mySourceManager.addMesh("helix",new ngl::Obj("models/Helix.obj"));
    mySourceManager.addMesh("spaceship",new ngl::Obj("models/Helix.obj"));

    //LOADING MAP
    TxtParser *myParser;
    myParser->loadLevelSources(0, mySourceManager);
    myParser->loadMap(0,myObjectManager, mySourceManager);

    //LOADING THE MAIN CHARACTER: THE SPEEDBOAT
    Diagonal dCont;
    SpeedBoat mySpeedBoat(&dCont,mySourceManager.getMesh("helix"),0);
    myObjectManager.addDynamicObject(&mySpeedBoat);
    //myObjectManager.setSea(new Sea(3000));
    //myObjectManager.createTestLevel();

    //Loading and linking cameras
    myCameraManager.loadCameras();
    ngl::Camera *myCamera = myCameraManager.getFirstCamera();
    myCameraManager.setTarget(&mySpeedBoat);

    std::cout << "Testing..." << std::endl;


    //GAME LOOP
    while (myPlayerOptions.running)
    {

        readPlayerInput(myPlayerControls, myPlayerOptions);
        setCamera(myCamera,myCameraManager,myPlayerOptions);

        //myDynamicSeaElements[0]->info();
        myObjectManager.moveObjects();

        myCameraManager.updateCameras();
        //aerialCamera.setEye(ngl::Vec4(0,12,12+mySpeedBoat.getZ(),1));

        myRenderer.render(myObjectManager.getSea(),myObjectManager.getObjects(),*myCamera,1);

        std::cout << "GAMEMANAGER: DISTANCE TO THE BEACH: " << (SEA_DEPTH+mySpeedBoat.getZ()) << std::endl;

        //std::cin.ignore();
    }

    std::cout << "Tested" << std::endl;

    //std::cout << "End of test." << std::endl;
    return 0;
}


void readPlayerInput(PlayerControls &_playerControls, playerOptions &_playerOptions)
{
    SDL_Event event;

    SDL_PollEvent(&event);
    switch (event.type)
    {
        case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
            case SDLK_ESCAPE:
            _playerOptions.running = false;
            break;

            case SDLK_RIGHT:
            _playerControls.setRight(true);
            break;

            case SDLK_LEFT:
            _playerControls.setLeft(true);
            break;

            case SDLK_SPACE:
            _playerControls.setSpeedUp(true);
            break;

            case SDLK_BACKSPACE:
            _playerOptions.backCamera = true;
            break;

            case SDLK_c:
            _playerOptions.changeCamera = true;
            break;

            case SDLK_0:
            _playerOptions.debugMode = 0;
            break;

            case SDLK_1:
            _playerOptions.debugMode = 1;
            break;

            case SDLK_2:
            _playerOptions.debugMode = 2;


            /*
            case SDLK_UP:
            mySpeedBoat.moveUp();
            break;

            case SDLK_DOWN:
            mySpeedBoat.moveDown();
            break;

            case SDLK_x:
            mySpeedBoat.rotateInX();
            break;

            case SDLK_y:
            mySpeedBoat.rotateInY();
            break;

            case SDLK_z:
            mySpeedBoat.rotateInZ();
            break;
            */

        }
        break;

        case SDL_KEYUP:
        switch(event.key.keysym.sym)
        {
            case SDLK_RIGHT:
            _playerControls.setRight(false);
            break;

            case SDLK_LEFT:
            _playerControls.setLeft(false);
            break;

            case SDLK_SPACE:
            _playerControls.setSpeedUp(false);
            break;

            case SDLK_BACKSPACE:
            _playerOptions.backCamera = false;
            break;

            case SDLK_c:
            //this is unnecessary
            _playerOptions.changeCamera = false;
            break;
        }
        break;

        case SDL_QUIT:
            _playerOptions.running = false;
        break;
    }
}

void setCamera(ngl::Camera *&_cam, CameraManager &_cameraManager, playerOptions &_playerOptions)
{
    if (_playerOptions.backCamera)
        _cam = _cameraManager.getBackCamera();
    else
    {
        if (_playerOptions.changeCamera)
        {
            _cam = _cameraManager.getNextCamera();
            _playerOptions.changeCamera = false;
        }

        else
            _cam = _cameraManager.getCurrentCamera();
    }
}

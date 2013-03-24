#include <ngl/Obj.h>
//glew must be included first!
#include <iostream>
#include <ngl/VAOPrimitives.h>
#include <ngl/TransformStack.h>
#include "Renderer.h"
#include "SourceStore.h"
#include "SpeedBoat.h"
#include "Sea.h"
#include "Object.h"
#include "Behaviour.h"
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


void checkActiveObjects(std::vector<Object*> &_objects, ngl::Camera *_cam);
void updateObjects(std::vector<Object*> &_objects);
void checkCollisions(std::vector<Object*> &_objects, const Sea &_sea, PhysicsEngine *_physicsEngine);
void clearCollisionInformation(std::vector<Object*> &_objects);
void checkCollisionsWithSeaLimits(std::vector<Object*> &_objects, const Sea &_sea);

int main()
{

    static const int s_maximumFPS = 30;

    //NEEDED OBJECTS
    Renderer myRenderer;
    SourceStore mySourceStore;
    Sea mySea;
    std::vector<Object*> myObjects;
    CameraSet myCameraSet;
    playerOptions myPlayerOptions;
    Utilities myUtilities;

    myRenderer.initGLContext();

    //LOADING SOURCES AND MAP
    Parser *myParser = new TXTParser();
    myParser->loadSources(mySourceStore);
    myParser->loadMap(0, mySea, myObjects, mySourceStore);

    //LOADING THE MAIN CHARACTER: THE SPEEDBOAT
    Object* mySpeedBoat = new SpeedBoat();
    PlayerControls* myPlayerControls = new PlayerControls();
    mySpeedBoat->setBehaviour(myPlayerControls);
    mySpeedBoat->setMesh(mySourceStore.getMesh("speedboat"));
    myObjects.push_back(mySpeedBoat);

    //LOADING AND LINKING CAMERAS
    myCameraSet.loadCameras(myRenderer.getWindowWidth(),myRenderer.getWindowHeight());
    myCameraSet.setTarget(mySpeedBoat);

    //PHYSICS ENGINE
    PhysicsEngine *myPhysicsEngine = new BSpherePE();

    //TIMING
    Uint32 startingTick;
    int frameCounter = 0;
    Uint32 lastStartingSecond = SDL_GetTicks();
    int currentFPS;


    //GAME LOOP
    while (myPlayerOptions.running)
    {
        startingTick = SDL_GetTicks();

        myUtilities.readPlayerInput(*myPlayerControls, myPlayerOptions, myRenderer.isFullScreen());

        myUtilities.setWindow(myRenderer,myPlayerOptions);
        myUtilities.setCamera(myCameraSet, myRenderer, myPlayerOptions);

        if (!myPlayerOptions.pause)
        {
            checkActiveObjects(myObjects,myCameraSet.getCurrentCamera());
            updateObjects(myObjects);
            checkCollisions(myObjects, mySea, myPhysicsEngine);

            myCameraSet.updateCameras();

            myRenderer.render(mySea,myObjects,*myCameraSet.getCurrentCamera(),myPlayerOptions.debugMode);
        }

        myUtilities.regulateFPS(startingTick, frameCounter, lastStartingSecond, currentFPS, s_maximumFPS);

        std::cout << "WORKING AT "<< currentFPS <<" FPS" << std::endl;

        //std::cout << "GAMEMANAGER: DISTANCE TO THE BEACH: " << (SEA_DEPTH+mySpeedBoat.getPosition().m_z) << std::endl;

        //std::cin.ignore();
    }
    return 0;
}

void checkActiveObjects(std::vector<Object*> &_objects, ngl::Camera *_cam)
{
    float currentZ = _cam->getEye().m_z;
    float far = _cam->getFar();

    std::vector<Object*>::iterator lastO = _objects.end();
    for(std::vector<Object*>::iterator currentO=_objects.begin(); currentO!=lastO; ++currentO)
    {
        (*currentO)->checkActive(currentZ, far);
    }
}

void updateObjects(std::vector<Object*> &_objects)
{
    std::vector<Object*>::iterator endO = _objects.end();
    for(std::vector<Object*>::iterator currentO=_objects.begin(); currentO!=endO;++currentO)
    {
        if ((*currentO)->isActive())
            (*currentO)->update();
    }
}

void checkCollisions(std::vector<Object*> &_objects, const Sea &_sea, PhysicsEngine *_physicsEngine)
{

    clearCollisionInformation(_objects);

    std::vector<Object*>::iterator endO = _objects.end();
    std::vector<Object*>::iterator lastO = endO-1;

    for(std::vector<Object*>::iterator o1=_objects.begin(); o1!=lastO; ++o1)
    {
        if ((*o1)->isActive())
        {
            for(std::vector<Object*>::iterator o2=o1+1; o2!= endO; ++o2)
            {
                if ((*o2)->isActive())
                {
                    _physicsEngine->checkCollision(*o1,*o2);
                }
            }
        }
    }

    checkCollisionsWithSeaLimits(_objects, _sea);
}

void clearCollisionInformation(std::vector<Object*> &_objects)
{
    std::vector<Object*>::iterator endO = _objects.end();
    for(std::vector<Object*>::iterator currentO=_objects.begin(); currentO!=endO; ++currentO)
    {
        if ((*currentO)->isActive())
        {
            (*currentO)->setCollided(false);
            (*currentO)->getDOF().up = true;
            (*currentO)->getDOF().down = true;
            (*currentO)->getDOF().left = true;
            (*currentO)->getDOF().right = true;
            (*currentO)->getDOF().forward = true;
            (*currentO)->getDOF().backward = true;
        }
    }
}

void checkCollisionsWithSeaLimits(std::vector<Object*> &_objects, const Sea &_sea)
{
    std::vector<Object*>::iterator lastO = _objects.end();
    for(std::vector<Object*>::iterator currentO=_objects.begin(); currentO!=lastO; ++currentO)
    {
        if ((*currentO)->isActive())
        {
            if ((*currentO)->getPosition().m_x<-_sea.getWidth()/2.0)
            {
                (*currentO)->getDOF().left = false;
                (*currentO)->setCollided(true);
            }

            if ((*currentO)->getPosition().m_x>_sea.getWidth()/2.0)
            {
                (*currentO)->getDOF().right = false;
                (*currentO)->setCollided(true);
            }
        }
    }
}

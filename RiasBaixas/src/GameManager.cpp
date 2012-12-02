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


struct playerOptions
{
    bool running = true;
    int debugMode = 1;
    bool changeCamera = false;
    bool backCamera = false;
    bool pause = false;
    bool resizeWindow = false;
    bool changeToFullScreen = false;
    bool restoreWindow = false;
};

void readPlayerInput(PlayerControls &_playerControls, playerOptions &_playerOptions, bool _isfullScreen);
void setCamera(CameraManager &_cameraManager, const Renderer &_renderer, playerOptions &_playerOptions);
void setWindow(Renderer &_renderer, playerOptions &_playerOptions);

int main()
{

    //NEEDED OBJECTS
    Renderer myRenderer;
    SourceManager mySourceManager;
    ObjectManager myObjectManager;
    ControllerManager myControllerManager;
    CameraManager myCameraManager;
    playerOptions myPlayerOptions;

    myRenderer.initGLContext();

    //Loading models
    mySourceManager.addMesh("helix", new ngl::Obj("models/Helix.obj"));
    mySourceManager.addMesh("spaceship", new ngl::Obj("models/SpaceShip.obj"));

    //LOADING THE MAIN CHARACTER: THE SPEEDBOAT
    Diagonal dCont;
    Floating fCont;
    Horizontal hCont;
    Vertical vCont;

    SpeedBoat mySpeedBoat;
    PlayerControls myPlayerControls;
    //mySpeedBoat.setController(&myPlayerControls);
    myPlayerControls.setControlledObject(&mySpeedBoat);
    //mySpeedBoat.setMesh(mySourceManager.getMesh("spaceship"));
    myObjectManager.addObject(&mySpeedBoat);
    myControllerManager.addController(&myPlayerControls);
    myObjectManager.setCentralObject(&mySpeedBoat);
    myObjectManager.setFar(myCameraManager.getFar());

    //LOADING MAP
    Parser *myParser = new TXTParser();
    myParser->loadLevelSources(0, mySourceManager);
    myParser->loadMap(0, myObjectManager, myControllerManager, mySourceManager);

    //myObjectManager.setSea(new Sea(3000));
    //myObjectManager.createTestLevel();

    //Loading and linking cameras
    myCameraManager.loadCameras(myRenderer.getWindowWidth(),myRenderer.getWindowHeight());
    myCameraManager.setTarget(&mySpeedBoat);

    //PHYSICS ENGINE
    PhysicsEngine *myPhysicsEngine = new BSpherePE();

    //GAME LOOP
    while (myPlayerOptions.running)
    {

        readPlayerInput(myPlayerControls, myPlayerOptions, myRenderer.isFullScreen());
        setWindow(myRenderer,myPlayerOptions);
        setCamera(myCameraManager, myRenderer, myPlayerOptions);

        if (!myPlayerOptions.pause)
        {
            myObjectManager.checkActiveObjects();
            myControllerManager.updateControllers();
            myObjectManager.checkCollisions(myPhysicsEngine);

            myCameraManager.updateCameras();
        }

        //aerialCamera.setEye(ngl::Vec4(0,12,12+mySpeedBoat.getZ(),1));

        //mySpeedBoat.info();
        myRenderer.render(myObjectManager.sea(),myObjectManager.objects(),*myCameraManager.getCurrentCamera(),myPlayerOptions.debugMode);

        //std::cout << "GAMEMANAGER: DISTANCE TO THE BEACH: " << (SEA_DEPTH+mySpeedBoat.getPosition().m_z) << std::endl;

        //std::cin.ignore();
    }

    std::cout << "Tested" << std::endl;

    //std::cout << "End of test." << std::endl;
    return 0;
}


void readPlayerInput(PlayerControls &_playerControls, playerOptions &_playerOptions, bool _isfullScreen)
{
    SDL_Event event;

    SDL_PollEvent(&event);
    switch (event.type)
    {

        case SDL_QUIT:
        _playerOptions.running = false;
        break;

        case SDL_WINDOWEVENT:
        _playerOptions.resizeWindow = true;

        case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
            case SDLK_ESCAPE:
            {
            if (_isfullScreen)
                _playerOptions.restoreWindow = true;
            else
                _playerOptions.running = false;
            }
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
            break;

            case SDLK_PAUSE:
            _playerOptions.pause = !_playerOptions.pause;
            break;

            case SDLK_F11:
            if (!_isfullScreen)
                _playerOptions.changeToFullScreen = true;
            else
                _playerOptions.restoreWindow = true;
            break;
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
    }

}

void setWindow(Renderer &_renderer, playerOptions &_playerOptions)
{
    if (_playerOptions.resizeWindow)
    {
        _renderer.resizeWindow();
        _playerOptions.resizeWindow = false;
    }
    if (_playerOptions.changeToFullScreen)
    {
        _renderer.fullScreen();
        _playerOptions.changeToFullScreen = false;
    }
    if (_playerOptions.restoreWindow)
    {
        _renderer.restoreWindow();
        _playerOptions.restoreWindow = false;
    }

}

void setCamera(CameraManager &_cameraManager, const Renderer &_renderer, playerOptions &_playerOptions)
{
    if (_playerOptions.resizeWindow)//|| _playerOptions.changeToFullScreen || _playerOptions.restoreWindow)
    {
        _cameraManager.setShape(_renderer.getWindowWidth(), _renderer.getWindowHeight());
        _playerOptions.resizeWindow = false;
    }

    if (_playerOptions.backCamera)
    {
        if (!_cameraManager.isBackCameraActive())
            _cameraManager.changeToBackCamera();
    }
    else
    {
        if (_cameraManager.isBackCameraActive())
            _cameraManager.leaveBackCamera();
    }

    if (_playerOptions.changeCamera && !_cameraManager.isBackCameraActive())
    {
        _cameraManager.nextCamera();
        //_playerOptions.changeCamera == false;
    }

}

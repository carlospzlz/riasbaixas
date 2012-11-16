#include <ngl/Obj.h>
//glew must be included first!
#include <iostream>
#include <ngl/VAOPrimitives.h>
#include <ngl/TransformStack.h>
#include "include/Renderer.h"
#include "include/Models.h"
#include "SpeedBoat.h"
#include "Sea.h"
#include "SeaElement.h"
#include "MusselFarm.h"
#include "Controller.h"
#include "PlayerControls.h"
#include "Floating.h"


struct playerOptions
{
    bool running = true;
    int debugMode = 0;
    int camera;
};

void readPlayerInput(PlayerControls &_playerControls, playerOptions &_playerOptions);

int main()
{

    //Needed objects
    Renderer myRenderer;
    //Parser myParser;
    Models myModels;
    PlayerControls myPlayerControls;
    playerOptions myPlayerOptions;


    myRenderer.initGLContext();

    //Loading cameras
    ngl::Camera aerialCamera(ngl::Vec3(0,6,6),ngl::Vec3(0,0,0),ngl::Vec3(0,1,0),ngl::PERSPECTIVE);
    // set the shape using FOV 45 Aspect Ratio based on Width and Height
    // The final two are near and far clipping planes of 0.5 and 10
    aerialCamera.setShape(45,(float)720.0/576.0,0.05,350,ngl::PERSPECTIVE);


    myModels.addModel(0,"models/Helix.obj");
    myModels.addModel(1,"models/SpaceShip.obj");

    //World elements
    Sea mySea;
    std::vector<StaticSeaElement*> myStaticSeaElements;
    std::vector<DynamicSeaElement*> myDynamicSeaElements;
    //Parser myParser;



    //DYNAMIC
    SpeedBoat mySpeedBoat(&myPlayerControls,myModels.getModel(1));
    myDynamicSeaElements.push_back(&mySpeedBoat);

    //MUSSELFARMS
    myStaticSeaElements.push_back(new MusselFarm(ngl::Vec3(2,0,2)));
    myStaticSeaElements.push_back(new MusselFarm(ngl::Vec3(-2,0,2)));


    //Tell the world to the renderer
    std::vector<SeaElement*> allElements;

    std::vector<StaticSeaElement*>::iterator lastSse = myStaticSeaElements.end();
    for(std::vector<StaticSeaElement*>::iterator currentSse = myStaticSeaElements.begin(); currentSse!=lastSse; ++currentSse)
        allElements.push_back(*currentSse);


    std::vector<DynamicSeaElement*>::iterator lastDse = myDynamicSeaElements.end();
    for(std::vector<DynamicSeaElement*>::iterator currentDse = myDynamicSeaElements.begin(); currentDse!=lastDse; ++currentDse)
        allElements.push_back(*currentDse);


    myRenderer.setWorld(&mySea, &allElements);

    //myRenderer.render(aerialCamera);



    std::cout << "Testing..." << std::endl;


    //GAME LOOP
    while (myPlayerOptions.running)
    {

        readPlayerInput(myPlayerControls, myPlayerOptions);


        myDynamicSeaElements[0]->info();
        myDynamicSeaElements[0]->move();

        aerialCamera.setEye(ngl::Vec4(0,12,12+mySpeedBoat.getZ(),1));

        myRenderer.render(aerialCamera,1);

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
        }
        break;

        case SDL_QUIT:
            _playerOptions.running = false;
        break;
    }
}

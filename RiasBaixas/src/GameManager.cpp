#include <ngl/Obj.h>
//glew must be included first!
#include <iostream>
#include <ngl/VAOPrimitives.h>
#include <ngl/TransformStack.h>
#include "include/Renderer.h"
#include "include/Models.h"
#include "SpeedBoat.h"
#include "Sea.h"
#include "StaticSeaElement.h"
#include "MusselFarm.h"


void doMusselFarm(MusselFarm mf)
{

}

int main()
{


    Renderer myRenderer;
    myRenderer.initGLContext();

    //sleep(3);

    //Loading cameras
    ngl::Camera aerialCamera(ngl::Vec3(0,6,6),ngl::Vec3(0,0,0),ngl::Vec3(0,1,0),ngl::PERSPECTIVE);
    // set the shape using FOV 45 Aspect Ratio based on Width and Height
    // The final two are near and far clipping planes of 0.5 and 10
    aerialCamera.setShape(45,(float)720.0/576.0,0.05,350,ngl::PERSPECTIVE);

    Models myModels;
    myModels.addModel(0,"models/Helix.obj");
    myModels.addModel(1,"models/SpaceShip.obj");

    //World elements
    //Sea mySea;
    //std::vector<StaticSeaElements> myStaticSeaElements;
    //std::vector<DynamicSeaElements> myDynamicSeaElements;

    Sea mySea;
    SpeedBoat mySpeedBoat(myModels.getModel(1));
    MusselFarm mf1 = MusselFarm(ngl::Vec3(2,0,2));


    std::vector<StaticSeaElement> myStaticSeaElements;
    myStaticSeaElements.push_back(mf1);

    //doMusselFarm(myStaticSeaElements.pop_back());

    myRenderer.setWorld(&mySea, &mySpeedBoat);

    //myRenderer.render(aerialCamera);


    std::cout << "Testing..." << std::endl;


    bool running = true;
    SDL_Event event;

    while (running)
    {
        SDL_PollEvent(&event);
        switch (event.type)
        {
            case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                running = false;
                break;

                case SDLK_RIGHT:
                mySpeedBoat.moveRight();
                break;

                case SDLK_LEFT:
                mySpeedBoat.moveLeft();
                break;

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

            }
            break;

            case SDL_QUIT:
                running = false;
            break;
        }
        //mySpeedBoat.rotateInY();
        mySpeedBoat.floating();
        myRenderer.render(aerialCamera);
    }

    std::cout << "Tested" << std::endl;

    //std::cout << "End of test." << std::endl;
    return 0;
}

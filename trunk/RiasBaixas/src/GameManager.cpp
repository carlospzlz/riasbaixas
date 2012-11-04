#include <ngl/Obj.h>
//glew must be included first!
#include <iostream>
#include <ngl/VAOPrimitives.h>
#include <ngl/TransformStack.h>
#include "include/Renderer.h"
#include "include/Models.h"


int main()
{
    SDL_Event event;

    Renderer myRenderer;
    myRenderer.initGLContext();

    //Loading cameras
    ngl::Camera aerialCamera(ngl::Vec3(0,1,1),ngl::Vec3(0,0,0),ngl::Vec3(0,1,0),ngl::PERSPECTIVE);
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

    SpeedBoat mySpeedBoat(myModels.getModel(SPEEDBOAT));

    myRenderer.setWorld(mySpeedBoat);

    myRenderer.render(aerialCamera);


    std::cout << "Testing..." << std::endl;



    //std::cout << myModels.getModelName(SPEEDBOAT) << std::endl;
    //myModels.draw(SPEEDBOAT);
    //myModels.draw(1);
    //ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
    //ngl::ShaderLib *shader = ngl::ShaderLib::instance();
    //shader->setShaderParam4f("Colour",1,1,1,1);
    //ngl::TransformStack tstack;
    //tstack.pushTransform();
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    //tstack.setPosition(ngl::Vec3(0,0,0));
    //tstack.setScale(20,20,20);
    //loadMatricesToShader(tstack);
    //prim->draw("sphere");


    while (event.type!=SDL_QUIT && event.key.keysym.sym!=SDLK_ESCAPE)
        SDL_PollEvent(&event);

    std::cout << "Tested" << std::endl;

    //std::cout << "End of test." << std::endl;
    return 0;
}

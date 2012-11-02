#include <ngl/Obj.h>
//glew must be included first!
#include "include/Window.h"
#include <iostream>
#include "include/Models.h"


int main(int argc, char** argv)
{

    Models myModels;
    Window myWindow;

    std::cout << "Testing..." << std::endl;

    myWindow.initGLContext();

    std::cout << myModels.getModelName(SPEEDBOAT) << std::endl;
    myModels.addModel(0,"models/SpaceShip.obj");
    //myModels.draw(SPEEDBOAT);

    myWindow.flip();

    std::cin.ignore();
    std::cout << "Tested" << std::endl;

    //std::cout << "End of test." << std::endl;
    return 0;
}

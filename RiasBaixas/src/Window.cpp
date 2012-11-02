#include <ngl/Light.h>
#include <ngl/Material.h>
#include <ngl/Transformation.h>
#include <ngl/NGLInit.h>
#include <ngl/Obj.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include <ngl/Text.h>
#include <ngl/Util.h>
#include "include/Window.h"

bool Window::initGLContext()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return false;

    glClearColor(0.5, 0.5, 0.5, 1.0f);			   // Black Background
    // enable depth testing for drawing
    glEnable(GL_DEPTH_TEST);
    // we need to initialise the NGL lib, under windows and linux we also need to
    // initialise GLEW, under windows this needs to be done in the app as well
    // as the lib hence the WIN32 define


    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

    SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, 8);

    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);

    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);

    m_screen = SDL_SetVideoMode(1024, 720, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL);

    if (m_screen == NULL)
            return false;

    ngl::NGLInit *Init = ngl::NGLInit::instance();
    Init->initGlew();

    return true;

}

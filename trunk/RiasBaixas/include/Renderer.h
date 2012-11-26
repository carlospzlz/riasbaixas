#ifndef RENDERER_H
#define RENDERER_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <ngl/Camera.h>
#include <ngl/Light.h>
#include <ngl/Material.h>
#include <ngl/TransformStack.h>
#include <ngl/Text.h>
#include "Sea.h"
#include "Object.h"

class Renderer
{

private:
    SDL_Surface *m_screen;
    ngl::Light *m_light;
    ngl::Text *m_text;
    ngl::TransformStack m_transformStack;
    void drawVector(ngl::Vec4 _position, ngl::Vec4 _vector, ngl::Camera _cam);
    void loadMatricesToShader(ngl::TransformStack &_tx, ngl::Camera m_cam);
    void renderTextToSurface(std::string _line, int _x, int _y, SDL_Surface *_surface);

public:
    Renderer() { };
    bool initGLContext();
    void render(Sea *_sea, std::vector<Object*> _objects, ngl::Camera &_cam);
    void render(Sea *_sea, std::vector<Object*> _objects, ngl::Camera &_cam, int _debugMode);
    //void Renderer::loadMatricesToShader(ngl::TransformStack &_tx, ngl::Camera m_cam);

};

#endif // RENDERER_H

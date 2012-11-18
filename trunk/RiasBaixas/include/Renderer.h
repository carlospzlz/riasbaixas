#ifndef RENDERER_H
#define RENDERER_H

#include <SDL/SDL.h>
#include <ngl/Camera.h>
#include <ngl/Light.h>
#include <ngl/Material.h>
#include <ngl/TransformStack.h>
#include "Sea.h"
#include "Object.h"

class Renderer
{

private:
    ngl::Light *m_light;
    ngl::TransformStack m_transformStack;
    void Renderer::loadMatricesToShader(ngl::TransformStack &_tx, ngl::Camera m_cam);

public:
    Renderer() { };
    bool initGLContext();
    void render(Sea *_sea, std::vector<Object*> _objects, ngl::Camera &_cam);
    void render(Sea *_sea, std::vector<Object*> _objects, ngl::Camera &_cam, int debugMode);
    //void Renderer::loadMatricesToShader(ngl::TransformStack &_tx, ngl::Camera m_cam);

};

#endif // RENDERER_H

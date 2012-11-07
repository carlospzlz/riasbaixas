#ifndef RENDERER_H
#define RENDERER_H

#include <SDL/SDL.h>
#include <ngl/Camera.h>
#include <ngl/Light.h>
#include <ngl/Material.h>
#include <ngl/TransformStack.h>
#include "SpeedBoat.h"

class Renderer
{

private:
    ngl::Light *m_light;
    ngl::TransformStack m_transformStack;
    SpeedBoat *m_speedBoat;

public:
    Renderer() { };
    bool initGLContext();
    void setWorld(SpeedBoat *_sp);
    void render(ngl::Camera &_cam);
    void Renderer::loadMatricesToShader(ngl::TransformStack &_tx, ngl::Camera m_cam);

};

#endif // RENDERER_H

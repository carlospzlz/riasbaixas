#ifndef RENDERER_H
#define RENDERER_H

#include <SDL/SDL.h>
#include <ngl/Camera.h>
#include <ngl/Light.h>
#include <ngl/Material.h>
#include <ngl/TransformStack.h>
#include "SpeedBoat.h"
#include "Sea.h"
#include "StaticSeaElement.h"
#include "DynamicSeaElement.h"

class Renderer
{

private:
    ngl::Light *m_light;
    ngl::TransformStack m_transformStack;
    Sea *m_sea;
    SpeedBoat *m_speedBoat;
    std::vector<StaticSeaElement> *m_staticSeaElements;
    std::vector<DynamicSeaElement> *m_dynamicSeaElements;

public:
    Renderer() { };
    bool initGLContext();
    void setWorld(Sea *_sea, SpeedBoat *_sp, std::vector<StaticSeaElement> *_staticSeaElements);
    void render(ngl::Camera &_cam);
    void render(ngl::Camera &_cam, int debugMode);
    void Renderer::loadMatricesToShader(ngl::TransformStack &_tx, ngl::Camera m_cam);

};

#endif // RENDERER_H

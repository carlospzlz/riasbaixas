#ifndef DYNAMICSEAELEMENT_H
#define DYNAMICSEAELEMENT_H

#include <ngl/Vec3.h>
#include <ngl/Vec4.h>
#include <ngl/Obj.h>
#include <ngl/Transformation.h>
#include <ngl/Camera.h>

#include "SeaElement.h"
#include "StaticSeaElement.h"
#include "Controller.h"

class DynamicSeaElement : SeaElement
{

protected:
    ngl::Vec3 m_velocity;
    Controller *m_controller;
    DynamicSeaElement(ngl::Vec3 _pos, ngl::Vec4 _rot, ngl::Vec4 _sca, Controller *_controller, ngl::Obj *_model);

public:
    virtual void move();
    virtual void checkCollisionWith(StaticSeaElement _sse);
    virtual void checkCollisionWith(DynamicSeaElement _dse);
    void info();

};

#endif // DYNAMICSEAELEMENT_H

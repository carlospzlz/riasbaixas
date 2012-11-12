#ifndef DYNAMICSEAELEMENT_H
#define DYNAMICSEAELEMENT_H

#include <ngl/Vec3.h>
#include <ngl/Vec4.h>
#include <ngl/Obj.h>
#include "Controller.h"

class DynamicSeaElement
{

protected:
    ngl::Vec3 m_position;
    ngl::Vec4 m_rotation;
    ngl::Vec4 m_scale;
    ngl::Vec3 m_velocity;
    Controller *m_controller;
    ngl::Obj *m_model;

public:
    DynamicSeaElement(ngl::Vec3 _pos, ngl::Vec4 _rot, ngl::Vec4 _sca, Controller *_controller, ngl::Obj *_model);
    float getX() { return m_position.m_x; }
    float getY() { return m_position.m_y; }
    float getZ() { return m_position.m_z; }
    void setX(float _x) {m_position.m_x = _x; }
    void setY(float _y) {m_position.m_y = _y; }
    void setZ(float _z) {m_position.m_z = _z; }

    void draw(bool _debuggingMode);
    void move();

};

#endif // DYNAMICSEAELEMENT_H

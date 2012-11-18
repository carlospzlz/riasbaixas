#ifndef DYNAMICOBJECT_H
#define DYNAMICOBJECT_H

#include <ngl/Vec3.h>
#include <ngl/Vec4.h>
#include <ngl/Obj.h>
#include <ngl/Transformation.h>
#include <ngl/Camera.h>

#include "Object.h"
#include "Controller.h"

class DynamicObject : public Object
{

protected:
    ngl::Vec3 m_velocity;
    Controller *m_controller;
    DynamicObject(objectType _type, ngl::Obj *_mesh, std::string _primName, ngl::Vec3 _pos, ngl::Vec4 _rot, ngl::Vec4 _sca, int _dam, ngl::Vec3 _vel, Controller *_controller);

public:
    virtual void move();

};

#endif // DYNAMICOBJECT_H

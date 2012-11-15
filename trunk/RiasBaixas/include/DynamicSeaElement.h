#ifndef DYNAMICSEAELEMENT_H
#define DYNAMICSEAELEMENT_H

#include <ngl/Vec3.h>
#include <ngl/Vec4.h>
#include <ngl/Obj.h>
#include <ngl/Transformation.h>
#include <ngl/Camera.h>

#include "SeaElement.h"
#include "Controller.h"

class DynamicSeaElement : public SeaElement
{

protected:
    ngl::Vec3 m_velocity;
    Controller *m_controller;
    DynamicSeaElement(SeaElementType _type, ngl::Obj *_model, std::string _primName, ngl::Vec3 _pos, ngl::Vec4 _rot, ngl::Vec4 _sca, Controller *_controller);

public:
    void move();
    void info();

};

#endif // DYNAMICSEAELEMENT_H

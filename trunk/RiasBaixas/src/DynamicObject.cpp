#include "DynamicObject.h"

DynamicObject::DynamicObject(objectType _type, ngl::Obj *_mesh, std::string _primName, ngl::Vec3 _pos, ngl::Vec4 _rot, ngl::Vec4 _sca, int _dam, ngl::Vec3 _vel, Controller *_controller)
    : Object(_type, _mesh, _primName, _pos, _rot, _sca, _dam)
{
    m_controller = _controller;
    m_velocity = _vel;
    std::cout << "DO created : ";
}

void DynamicObject::move()
{
    std::cout << "No movement defined for this concrete DO" << std::endl;
}

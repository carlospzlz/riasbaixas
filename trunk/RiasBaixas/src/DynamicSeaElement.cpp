#include "DynamicSeaElement.h"

DynamicSeaElement::DynamicSeaElement(SeaElementType _type, ngl::Obj *_model, std::string _primName, ngl::Vec3 _pos, ngl::Vec4 _rot, ngl::Vec4 _sca, ngl::Vec3 _vel, Controller *_controller)
    : SeaElement(_type, _model, _primName, _pos, _rot, _sca)
{
    m_controller = _controller;
    m_velocity = _vel;
    std::cout << "DSE created : ";
}

void DynamicSeaElement::move()
{
    std::cout << "No movement defined for this concrete DSE" << std::endl;
}

/*
void DynamicSeaElement::info()
{
    std::cout << "this is a DSE" << std::endl;
}*/

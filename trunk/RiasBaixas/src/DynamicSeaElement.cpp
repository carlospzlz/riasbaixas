#include "DynamicSeaElement.h"

DynamicSeaElement::DynamicSeaElement(ngl::Vec3 _pos, ngl::Vec4 _rot, ngl::Vec4 _sca, Controller *_controller, ngl::Obj *_model)
    : SeaElement(_model, _primName, _pos, _rot, _sca)
{
    m_controller = _controller;
    m_velocity = ngl::Vec3(0,0,1);
    std::cout << "DSE created : ";
}

void DynamicSeaElement::info()
{
    std::cout << "DSE info:" << std::endl;
    std::cout << "P-> " << m_position << std::endl;
    std::cout << "R-> " << m_rotation << std::endl;
    std::cout << "S-> " << m_scale << std::endl << std::endl;
}

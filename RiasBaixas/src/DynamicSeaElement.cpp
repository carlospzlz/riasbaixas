#include "DynamicSeaElement.h"

DynamicSeaElement::DynamicSeaElement(SeaElementType _type, ngl::Obj *_model, std::string _primName, ngl::Vec3 _pos, ngl::Vec4 _rot, ngl::Vec4 _sca, Controller *_controller)
    : SeaElement(_type, _model, _primName, _pos, _rot, _sca)
{
    m_controller = _controller;
    m_velocity = ngl::Vec3(0,0,1);
    std::cout << "DSE created : ";
}

void DynamicSeaElement::move()
{

}

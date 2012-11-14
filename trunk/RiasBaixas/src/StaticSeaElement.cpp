#include "StaticSeaElement.h"

StaticSeaElement::StaticSeaElement(SeaElementType _type, ngl::Obj *_model, std::string _primName, ngl::Vec3 _pos, ngl::Vec4 _rot, ngl::Vec4 _sca)
    : SeaElement(_type, _model, _primName, _pos, _rot, _sca)
{
    std::cout << "SSE created : ";
}

void StaticSeaElement::info()
{
    std::cout << "SSE info:" << std::endl;
    std::cout << "P-> " << m_position << std::endl;
    std::cout << "R-> " << m_rotation << std::endl;
    std::cout << "S-> " << m_scale << std::endl << std::endl;
}

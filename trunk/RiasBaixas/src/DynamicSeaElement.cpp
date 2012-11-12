#include "DynamicSeaElement.h"

DynamicSeaElement::DynamicSeaElement(ngl::Vec3 _pos, ngl::Vec4 _rot, ngl::Vec4
                  _sca, Controller *_controller, ngl::Obj *_model)
{
    m_position = _pos;
    m_rotation = _rot;
    m_scale = _sca;
    m_controller = _controller;
    m_model = _model;
}

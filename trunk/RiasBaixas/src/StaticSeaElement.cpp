#include "StaticSeaElement.h"

StaticSeaElement::StaticSeaElement(ngl::Obj *_model,  std::string _prim,  ngl::Vec3 _pos)
{
    m_model = _model;
    m_primForDebugging = _prim;
    m_position = _pos;
}

void StaticSeaElement::draw(bool _debuggingMode)
{
    if (_debuggingMode || !m_model)
    {
        ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
        prim->draw(m_primForDebugging);
    }
    else
    {
        //ngl::ShaderLib *shader = ngl::ShaderLib::instance();
        //(*shader)[_shader]->use();

        //m_transform.setPosition(m_position);

        //ngl::Mat4 MVP=m_transform.getMatrix()*_cam->getVPMatrix();

        //shader->setShaderParamFromMat4("MVP",MVP);
        //m_model->draw();
    }
}

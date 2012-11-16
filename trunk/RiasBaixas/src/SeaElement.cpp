#include <SeaElement.h>
#include <iostream>

SeaElement::SeaElement(SeaElementType _type, ngl::Obj *_model, std::string _primName, ngl::Vec3 _pos, ngl::Vec4 _rot, ngl::Vec4 _sca)
{
    m_type = _type;
    m_model = _model;
    m_primName = _primName;
    m_position = _pos;
    m_rotation = _rot;
    m_scale = _sca;
    std::cout << "SE created : " << std::endl;
}

void SeaElement::draw(const std::string &_shader, const ngl::Camera &_cam, int _debugMode)
{
    ngl::ShaderLib *shader = ngl::ShaderLib::instance();
    (*shader)[_shader]->use();

    m_transform.setPosition(m_position);
    m_transform.setRotation(m_rotation);
    m_transform.setScale(m_scale);

    ngl::Mat4 MVP=m_transform.getMatrix()*_cam.getVPMatrix();

    shader->setShaderParamFromMat4("MVP",MVP);

    if (_debugMode == 1 || !m_model)
        ngl::VAOPrimitives::instance()->draw(m_primName);
    else if (_debugMode == 2)
        m_model->drawBBox();
    else
        m_model->draw();
}


void SeaElement::info()
{
    std::cout << "SE info of " << this << " (type "<< m_type << ")" << std::endl;
    std::cout << "P-> " << m_position << std::endl;
    std::cout << "R-> " << m_rotation << std::endl;
    std::cout << "S-> " << m_scale << std::endl << std::endl;
}

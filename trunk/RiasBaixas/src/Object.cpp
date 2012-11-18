#include <iostream>

#include "Object.h"

Object::Object(objectType _type, ngl::Obj *_mesh, std::string _primName, ngl::Vec3 _pos, ngl::Vec4 _rot, ngl::Vec4 _sca, int _dam)
{
    m_type = _type;
    m_mesh = _mesh;
    m_primName = _primName;
    m_position = _pos;
    //clamping to the Sea limits
    m_position.m_x = std::max(-SEA_WIDTH/(float)2, m_position.m_x);
    m_position.m_x = std::min(SEA_WIDTH/(float)2, m_position.m_x);
    m_rotation = _rot;
    m_scale = _sca;
    m_damage = _dam;
    std::cout << "Object created : ";
}

void Object::draw(const std::string &_shader, const ngl::Camera &_cam, int _debugMode)
{
    ngl::ShaderLib *shader = ngl::ShaderLib::instance();
    (*shader)[_shader]->use();

    m_transform.setPosition(m_position);
    m_transform.setRotation(m_rotation);
    m_transform.setScale(m_scale);

    ngl::Mat4 MVP=m_transform.getMatrix()*_cam.getVPMatrix();

    shader->setShaderParamFromMat4("MVP",MVP);

    if (_debugMode == 1 || !m_mesh)
    {
        //m_transform.set
        ngl::VAOPrimitives::instance()->draw(m_primName);
    }
    else if (_debugMode == 2)
        m_mesh->drawBBox();
    else
        m_mesh->draw();
}


void Object::info()
{
    std::cout << "Object info of " << this << " (type "<< m_type << ")" << std::endl;
    std::cout << "P-> " << m_position << std::endl;
    std::cout << "R-> " << m_rotation << std::endl;
    std::cout << "S-> " << m_scale << std::endl << std::endl;
}

/*
void Object::interactWith()
{
    std::cout << "No specific behaviour defined for interactWith" << std::endl;
}
*/

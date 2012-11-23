#include <iostream>

#include "Object.h"


Object::Object()
{
    m_active = false;
    m_position = ngl::Vec3(0,0,0);
    m_previousPos = m_position;
    m_rotation = ngl::Vec3(0,0,0);
    m_scale = ngl::Vec3(1,1,1);
    m_velocity = ngl::Vec3(0,0,0);
    m_maxSpeed = 0;
    m_mass = 1;
    m_type = ot_object;
    m_mesh = NULL;
    m_primName = "cube";
    m_damage = 0;
    m_jumping = false;
    m_transform.reset();
    m_controller = NULL;

}

void Object::setPosition(ngl::Vec3 _pos)
{
    m_position = _pos;
    m_position.m_x = std::max(-SEA_WIDTH/(float)2, m_position.m_x);
    m_position.m_x = std::min(SEA_WIDTH/(float)2, m_position.m_x);
    if (_pos.m_x<-SEA_WIDTH/2.0 || _pos.m_x>SEA_WIDTH/2.0)
        std::cout << "Object: Warning: position out of the Sea" << std::endl;
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
    std::cout << "Position -> " << m_position << std::endl;
    std::cout << "Rotation -> " << m_rotation << std::endl;
    std::cout << "Scale -> " << m_scale << std::endl << std::endl;
    std::cout << "Velocity -> "<< m_velocity << std::endl << std::endl;
}

void Object::update(float _currentZ, float _far)
{
    m_active = (m_position.m_z > _currentZ-_far) && (m_position.m_z < _currentZ+_far);
    m_previousPos = m_position;

    if (m_active && m_controller)
    {
        m_controller->move(m_position,m_rotation,m_velocity,m_maxSpeed,m_jumping,m_degreesOfFreedom);
        info();
    }

    //std::cout << m_position.m_z << " " << _currentZ << " " << _far << " " << m_active << std::endl;
    //std::cout << "Object: Warning: Undefined specific update method for this object" << std::endl;
}

void Object::collisionEvent(Object _o)
{
    std::cout << "Object: Warning: Undefined collisionEvent method for this object" << std::endl;
}


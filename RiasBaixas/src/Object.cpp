#include <iostream>

#include "Object.h"


Object::Object()
{
    m_active = false;
    m_transform.setPosition(ngl::Vec4(0,0,0,1));
    m_transform.setRotation(ngl::Vec4(0,0,0,1));
    m_transform.setScale(ngl::Vec4(1,1,1,1));
    m_previousTransform = m_transform;
    m_velocity = ngl::Vec3(0,0,0);
    m_angularVelocity = ngl::Vec3(0,0,0);
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

void Object::setPosition(ngl::Vec4 _pos)
{
    _pos.m_x = std::max(-SEA_WIDTH/(float)2, _pos.m_x);
    _pos.m_x = std::min(SEA_WIDTH/(float)2, _pos.m_x);
    m_transform.setPosition(_pos);
    if (_pos.m_x<-SEA_WIDTH/2.0 || _pos.m_x>SEA_WIDTH/2.0)
        std::cout << "Object: Warning: position out of the Sea" << std::endl;
}

/*
void Object::draw(const std::string &_shader, const ngl::Camera &_cam, int _debugMode)
{
    ngl::ShaderLib *shader = ngl::ShaderLib::instance();
    (*shader)[_shader]->use();

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
*/

void Object::info()
{
    std::cout << "Object info of " << this << " (type "<< m_type << ")" << std::endl;
    std::cout << "Position -> " << m_transform.getPosition() << std::endl;
    std::cout << "Rotation -> " << m_transform.getRotation() << std::endl;
    std::cout << "Scale -> " << m_transform.getScale() << std::endl << std::endl;
    std::cout << "Linear Velocity -> "<< m_velocity << std::endl << std::endl;
    std::cout << "Angular Velocity -> "<< m_angularVelocity << std::endl << std::endl;
}

void Object::update(float _currentZ, float _far)
{
    m_active = (m_transform.getPosition().m_z > _currentZ-_far) && (m_transform.getPosition().m_z < _currentZ+_far);
    m_previousTransform = m_transform;

    if (m_active && m_controller)
    {
        m_controller->move(m_transform,m_velocity, m_angularVelocity,m_degreesOfFreedom,m_jumping);
        info();
    }

    //std::cout << m_position.m_z << " " << _currentZ << " " << _far << " " << m_active << std::endl;
    //std::cout << "Object: Warning: Undefined specific update method for this object" << std::endl;
}

void Object::collisionEvent(Object _o)
{
    std::cout << "Object: Warning: Undefined collisionEvent method for this object" << std::endl;
}


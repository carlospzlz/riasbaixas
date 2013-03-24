#include <iostream>

#include "Object.h"


Object::Object()
{
    m_active = false;
    m_behaviour = NULL;
    m_transform.reset();
    //m_transform.setPosition(ngl::Vec4(0,0,0,1));
    //m_transform.setRotation(ngl::Vec4(0,0,0,1));
    //m_transform.setScale(ngl::Vec4(1,1,1,1));
    m_previousTransform = m_transform;
    m_mass = 1;
    m_velocity = ngl::Vec3(0,0,0);
    m_maxSpeed = 0.02;
    m_type = ot_object;
    m_mesh = NULL;
    m_primName = "cube";
    m_bSRadius = 1;
    m_damage = 0;
    m_collided = false;
    m_degreesOfFreedom.forward = true;
    m_degreesOfFreedom.backward = true;
    m_degreesOfFreedom.up = true;
    m_degreesOfFreedom.down = true;
    m_degreesOfFreedom.left = true;
    m_degreesOfFreedom.right = true;

}

void Object::setBehaviour(Behaviour *b)
{
    m_behaviour = b;
    b->setAcceleration(m_mass);
}

void Object::setPosition(ngl::Vec4 _pos)
{
    m_transform.setPosition(_pos);
    //take care with this, might give problems for checkings, but looks good..
    //if there is no mass, you just change the position once!
    //if (!m_mass)
    //    m_previousTransform.setPosition(_pos);
}

void Object::setMesh(ngl::Obj* _obj)
{
    if (_obj)
    {
        m_mesh = _obj;
        m_bSRadius = _obj->getSphereRadius();
    }
}

void Object::info()
{
    std::cout << "Object info of " << this << " (type "<< m_type << ")" << std::endl;
    std::cout << "Position -> " << m_transform.getPosition() << std::endl;
    std::cout << "PreviousPos -> " << m_previousTransform.getPosition() << std::endl;
    std::cout << "Rotation -> " << m_transform.getRotation() << std::endl;
    std::cout << "Scale -> " << m_transform.getScale() << std::endl;
    std::cout << "Linear Velocity -> "<< m_velocity << std::endl;
    std::cout << "Angular Velocity -> "<< m_angularVelocity << std::endl;
    std::cout << "Degrees Of Freedom:" << std::endl;
    std::cout << "  " << m_degreesOfFreedom.forward << std::endl;
    std::cout << m_degreesOfFreedom.left << "   " << m_degreesOfFreedom.right << std::endl;
    std::cout << "  " << m_degreesOfFreedom.backward << std::endl;
    std::cout << "Strategy -> " << ( m_behaviour ? m_behaviour->getName() : "NULL" ) << std::endl;


}

void Object::update()
{
    //it might be a static object!! (musselFarm)
    if (m_behaviour)
    {
        m_previousTransform.setPosition(m_transform.getPosition());
        m_previousTransform.setRotation(m_transform.getRotation());
        m_behaviour->move(m_transform, m_velocity, m_angularVelocity, m_degreesOfFreedom);
    }
}

std::string Object::getType()
{
    if (m_type==ot_speedBoat)
        return "Speedboat";
    else if (m_type==ot_musselFarm)
        return "MusselFarm";
    else if (m_type==ot_fisherBoat)
        return "FisherBoat";
    else
        return "other";

}

void Object::checkActive(float _currentZ, float _far)
{
    m_active = (m_transform.getPosition().m_z > _currentZ-_far) && (m_transform.getPosition().m_z < _currentZ+_far);
    //m_previousTransform = m_transform; because if not, static objects disapear at collisions, the recover a position
    //which was never set
}

void Object::collisionEvent(Object &_o)
{
    //std::cout << "Object: Warning: Undefined collisionEvent method for this object" << std::endl;
}


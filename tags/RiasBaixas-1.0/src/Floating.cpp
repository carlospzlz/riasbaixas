#include "Floating.h"


void Floating::move()
{

    ngl::Vec4 velocity = m_object->getVelocity();
    velocity.m_y = floatingVelocity();

    //FRICTION FORCE IN CASE IT'S MOVING

    //in X
    if (velocity.m_x < -m_acceleration.m_x)
        velocity.m_x += m_acceleration.m_x;
    else if (velocity.m_x > m_acceleration.m_x)
        velocity.m_x -= m_acceleration.m_x;
    else
        velocity.m_x = 0;

    //in Z
    if (velocity.m_z < -m_acceleration.m_z)
        velocity.m_z += m_acceleration.m_z;
    else if (velocity.m_z > m_acceleration.m_z)
        velocity.m_z -= m_acceleration.m_z;
    else
        velocity.m_z = 0;

    m_object->setVelocity(velocity);

    Controller::move();

}

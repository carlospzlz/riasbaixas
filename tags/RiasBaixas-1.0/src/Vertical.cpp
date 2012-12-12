#include "Vertical.h"

Vertical::Vertical()
{
    m_goingForward = false;
}

void Vertical::move()
{
    ngl::Vec4 velocity = m_object->getVelocity();

    if (m_goingForward)
        velocity.m_z -= CONTROLLER_MOTOR_FORCE;
    else
        velocity.m_z += CONTROLLER_MOTOR_FORCE;

    velocity.m_z = std::max(velocity.m_z, (float)-CONTROLLER_SPEED);
    velocity.m_z = std::min(velocity.m_z, (float)CONTROLLER_SPEED);

    //Friction force in Z
    if (velocity.m_x < -CONTROLLER_FRICTION_FORCE)
        velocity.m_x += CONTROLLER_FRICTION_FORCE;
    else if (velocity.m_x > CONTROLLER_FRICTION_FORCE)
        velocity.m_x -= CONTROLLER_FRICTION_FORCE;
    else
        velocity.m_x = 0;

    //Floating in Y
    velocity.m_y = floatingVelocity();

    m_object->setVelocity(velocity);

    Controller::move();

}

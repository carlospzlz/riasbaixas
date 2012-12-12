#include <Horizontal.h>

Horizontal::Horizontal()
{
    m_goingRight = true;
}

void Horizontal::move()
{
    ngl::Vec4 velocity = m_object->getVelocity();

    if (m_goingRight)
        velocity.m_x += CONTROLLER_MOTOR_FORCE;
    else
        velocity.m_x -= CONTROLLER_MOTOR_FORCE;

    velocity.m_x = std::max(velocity.m_x, (float)-CONTROLLER_SPEED);
    velocity.m_x = std::min(velocity.m_x, (float)CONTROLLER_SPEED);

    if (!m_object->getDOF().right)
        m_goingRight = false;
    if (!m_object->getDOF().left)
        m_goingRight = true;

    //Friction force in Z
    if (velocity.m_z < -CONTROLLER_FRICTION_FORCE)
        velocity.m_z += CONTROLLER_FRICTION_FORCE;
    else if (velocity.m_z > CONTROLLER_FRICTION_FORCE)
        velocity.m_z -= CONTROLLER_FRICTION_FORCE;
    else
        velocity.m_z = 0;

    //Floating in Y
    velocity.m_y = floatingVelocity();

    m_object->setVelocity(velocity);

    //std::cout << "Horizontal: Velocity.m_x = " << m_object->getVelocity().m_x << std::endl;

    Controller::move();

}

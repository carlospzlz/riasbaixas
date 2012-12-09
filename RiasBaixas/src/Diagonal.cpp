#include "Diagonal.h"
#include "Sea.h"

Diagonal::Diagonal()
{
    m_angle = 0;
    m_quadrant = 1;
}

void Diagonal::move()
{
    ngl::Vec4 position = m_object->getPosition();
    ngl::Vec4 rotation = m_object->getRotation();
    float mass = m_object->getMass();
    float maxSpeed = m_object->getMaxSpeed();
    float maxCamber = m_object->getMaxCamber();
    ngl::Vec4 velocity = m_object->getVelocity();
    ngl::Vec4 angularVelocity;

    m_angle = rotation.m_y;
    m_angle = m_angle % 360;

    //FIRST QUADRANT
    if (m_quadrant == 1)
    {
        if (m_angle > 45-CONTROLLER_ANGULAR_VELOCITY && m_angle < 45+CONTROLLER_ANGULAR_VELOCITY)
            angularVelocity.m_y = 0;
        else if (m_angle > 45 && m_angle <= 135)
        {
            angularVelocity.m_y = -CONTROLLER_ANGULAR_VELOCITY;
            angularVelocity.m_x = CONTROLLER_ANGULAR_VELOCITY;
        }
        else
        {
            angularVelocity.m_y = CONTROLLER_ANGULAR_VELOCITY;
            angularVelocity.m_x = -CONTROLLER_ANGULAR_VELOCITY;
        }
        velocity.m_x += m_acceleration.m_x;
        velocity.m_z -= m_acceleration.m_z;
    }

    //SECOND QUADRANT
    if (m_quadrant == 2)
    {
        if (m_angle > 135-CONTROLLER_ANGULAR_VELOCITY && m_angle < 135+CONTROLLER_ANGULAR_VELOCITY)
            angularVelocity.m_y = 0;
        else if (m_angle > 135 && m_angle < 315)
        {
            angularVelocity.m_y = -CONTROLLER_ANGULAR_VELOCITY;
            angularVelocity.m_x = CONTROLLER_ANGULAR_VELOCITY;
        }
        else
        {
            angularVelocity.m_y = CONTROLLER_ANGULAR_VELOCITY;
            angularVelocity.m_x = -CONTROLLER_ANGULAR_VELOCITY;
        }
        velocity.m_x -= m_acceleration.m_x;
        velocity.m_z -= m_acceleration.m_z;
    }

    //THIRD QUADRANT
    if (m_quadrant == 3)
    {
        if (m_angle > 225-CONTROLLER_ANGULAR_VELOCITY && m_angle < 225+CONTROLLER_ANGULAR_VELOCITY)
            angularVelocity.m_y = 0;
        else if (m_angle > 45 && m_angle < 225)
        {
            angularVelocity.m_y = CONTROLLER_ANGULAR_VELOCITY;
            angularVelocity.m_x = -CONTROLLER_ANGULAR_VELOCITY;
        }
        else
        {
            angularVelocity.m_y = -CONTROLLER_ANGULAR_VELOCITY;
            angularVelocity.m_x = CONTROLLER_ANGULAR_VELOCITY;
        }
        velocity.m_x -= m_acceleration.m_x;
        velocity.m_z += m_acceleration.m_z;
    }

    //FORTH QUADRANT
    if (m_quadrant == 4)
    {
        if (m_angle > 315-CONTROLLER_ANGULAR_VELOCITY && m_angle < 315+CONTROLLER_ANGULAR_VELOCITY)
            angularVelocity.m_y = 0;
        else if (m_angle > 135 && m_angle < 315)
        {
            angularVelocity.m_y = CONTROLLER_ANGULAR_VELOCITY;
            angularVelocity.m_x = -CONTROLLER_ANGULAR_VELOCITY;
        }
        else
        {
            angularVelocity.m_y = -CONTROLLER_ANGULAR_VELOCITY;
            angularVelocity.m_x = CONTROLLER_ANGULAR_VELOCITY;
        }
        velocity.m_x += m_acceleration.m_x;
        velocity.m_z += m_acceleration.m_z;
    }

    //CLAMPING TO MAXIMUM ROTATION IN X
    if (rotation.m_x>CONTROLLER_CAMBER || rotation.m_x<-CONTROLLER_CAMBER )
        angularVelocity.m_x = 0;

    //RECOVER CAMBER IN X
    if (angularVelocity.m_y == 0)
    {
        if (rotation.m_x<-CONTROLLER_ANGULAR_VELOCITY)
               angularVelocity.m_x = CONTROLLER_ANGULAR_VELOCITY;
        else if ( rotation.m_x>CONTROLLER_ANGULAR_VELOCITY)
                angularVelocity.m_x = -CONTROLLER_ANGULAR_VELOCITY;
        else
            angularVelocity.m_x = 0;
    }

    //COLLISIONS WITH SEA LIMITS (MODIFY THIS WHEN ADDING DEGREES FO FREEDOM)
    if (!m_object->getDOF().right)
    {
        if (m_quadrant == 1)
            m_quadrant = 2;
        if (m_quadrant == 4)
            m_quadrant = 3;
    }

    if (!m_object->getDOF().left)
    {
        if (m_quadrant == 2)
            m_quadrant = 1;
        if (m_quadrant == 3)
            m_quadrant = 4;
    }

    //CLAMPING

    velocity.m_z = std::max(velocity.m_z, (float)-CONTROLLER_SPEED);
    velocity.m_z = std::min(velocity.m_z, (float)CONTROLLER_SPEED);

    velocity.m_x = std::max(velocity.m_x, (float)-CONTROLLER_SPEED);
    velocity.m_x = std::min(velocity.m_x, (float)CONTROLLER_SPEED);

    //FLOATING MOVEMENT IN Y

    velocity.m_y = floatingVelocity();

    //std::cout << "DIAGONAL: { quadrant: " << m_quadrant << ", angle: " << m_angle << "}" << std::endl;

    m_object->setVelocity(velocity);
    m_object->setAngularVelocity(angularVelocity);

    Controller::move();

}

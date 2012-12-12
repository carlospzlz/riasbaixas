#include <PlayerControls.h>


PlayerControls::PlayerControls()
{
    m_left = false;
    m_right = false;
    m_speedUp = false;
    m_floating = true;
    m_ticksBouncing = 0;

}

void PlayerControls::move()
{
    //std::cout << "PlayerControls: player controlling [" << m_left << " "<< m_speedUp << " "<< m_right << "]"<< std::endl;

    //m_acceleration = ngl::Vec4(CONTROLLER_MOTOR_FORCE/m_object->getMass(),CONTROLLER_MOTOR_FORCE/m_object->getMass(),CONTROLLER_MOTOR_FORCE/m_object->m_getMass(),1);

    if (m_speedUp)
        m_object->setMaxSpeed((float)PLAYERCONTROLS_HIGHSPEED);
    else
        m_object->setMaxSpeed((float)CONTROLLER_SPEED);


    ngl::Vec4 position = m_object->getPosition();
    ngl::Vec4 rotation = m_object->getRotation();
    float maxSpeed = m_object->getMaxSpeed();
    float maxCamber = m_object->getMaxCamber();
    ngl::Vec4 velocity = m_object->getVelocity();
    ngl::Vec4 angularVelocity;


    if (m_object->isJumping())
        std::cout << "it jumps" << std::endl;
    else
    {
        //MOVING IN X
        if (m_left && !m_right)
        {
            //comber left
            velocity.m_x += -m_acceleration.m_x;
            angularVelocity.m_y = CONTROLLER_ANGULAR_VELOCITY;
            angularVelocity.m_x = -CONTROLLER_ANGULAR_VELOCITY;
        }

        if (m_right && !m_left)
        {
            //comber right
            velocity.m_x += m_acceleration.m_x;
            angularVelocity.m_y = -CONTROLLER_ANGULAR_VELOCITY;
            angularVelocity.m_x = CONTROLLER_ANGULAR_VELOCITY;
        }


        if (rotation.m_x > maxCamber || rotation.m_x < -maxCamber)
            angularVelocity.m_x = 0;
        if (rotation.m_y > 90+ maxCamber || (rotation.m_y < 90 -maxCamber))
            angularVelocity.m_y = 0;


        //recover velocity and comber

        if ((!m_left && !m_right) || (m_left && m_right))
        {
            //recover velocity

            if (velocity.m_x > m_acceleration.m_x)
                velocity.m_x -= m_acceleration.m_x;
            else if (velocity.m_x < -m_acceleration.m_x)
                velocity.m_x += m_acceleration.m_x;
            else
                velocity.m_x = 0;

            //recover comber in Y
            if (rotation.m_y < 90)
                angularVelocity.m_y = CONTROLLER_ANGULAR_VELOCITY;
            else if (rotation.m_y > 90)
                angularVelocity.m_y = -CONTROLLER_ANGULAR_VELOCITY;
            else
                angularVelocity.m_y = 0;

            //recover comber in X
            if (rotation.m_x > 0)
                angularVelocity.m_x = -CONTROLLER_ANGULAR_VELOCITY;
            else if (rotation.m_x < 0)
                angularVelocity.m_x = CONTROLLER_ANGULAR_VELOCITY;
            else
                angularVelocity.m_x = 0;
        }

        //campling velocity in x
        velocity.m_x = std::min(velocity.m_x, (float)PLAYERCONTROLS_HIGHSPEED_X);
        velocity.m_x = std::max(velocity.m_x, (float)-PLAYERCONTROLS_HIGHSPEED_X);

        //DECIDE IF LATERAL STREAM FORCES OR THE BOAT STOP IN DRY
        //if ( (_transform.getPosition().m_x<-SEA_WIDTH/2.0 && m_left) || (_transform.getPosition().m_x>SEA_WIDTH/2.0 && m_right) || (m_left && m_right))
        //    _vel.m_x = 0;
        if ( position.m_x<-SEA_WIDTH/2.0 )
            velocity.m_x += PLAYERCONTROLS_LATERAL_STREAM_FORCE;
        if ( position.m_x>SEA_WIDTH/2.0 )
            velocity.m_x -= PLAYERCONTROLS_LATERAL_STREAM_FORCE;


        //MOVING IN Y
        //State machine
        if (m_floating)
        {
            velocity.m_y = floatingVelocity();
            if (m_speedUp)
            {
                m_floating = false;
                m_emerging = true;
            }
        }

        if (m_emerging)
        {
            velocity.m_y += m_acceleration.m_y;
            velocity.m_y = std::min(velocity.m_y, (float)CONTROLLER_SPEED);
            if (position.m_y>PLAYERCONTROLS_EMERSION_HIGH)
            {
                m_emerging = false;
                m_bouncing = true;
                m_ticksBouncing = 0;
                velocity.m_y = 0;
            }
            if (!m_speedUp)
            {
                m_emerging = false;
                m_immersing = true;
            }
        }

        if (m_bouncing)
        {
            velocity.m_y = PLAYERCONTROLS_AMPLITUDE_BOUNCING*std::sin(PLAYERCONTROLS_FRECUENCY_BOUNCING*m_ticksBouncing);
             ++m_ticksBouncing;
            if (!m_speedUp)
            {
                m_bouncing = false;
                m_immersing = true;
            }
        }

        if (m_immersing)
        {
           velocity.m_y -= CONTROLLER_FRICTION_FORCE;
           velocity.m_y = std::max(velocity.m_y, (float)-CONTROLLER_SPEED);
           if (position.m_y<SEA_FLOATING_HIGH)
           {
               m_immersing = false;
               m_floating = true;
               resetFloatingVelocity();
               velocity.m_y = 0;
           }
        }

        //MOVING IN Z

        //accelerating
        if (m_speedUp || velocity.m_z < CONTROLLER_SPEED)
            velocity.m_z -= m_acceleration.m_z;
        else
            velocity.m_z += m_acceleration.m_z;

        //velocity.m_z = std::max(std::abs(velocity.m_z), maxSpeed);
        velocity.m_z = -std::min(std::abs(velocity.m_z), maxSpeed);
    }

    //std::cout << "Player Controls: state: { " <<m_floating<< " " << m_emerging << " " << m_bouncing << " " << m_immersing << " } high "<< position.m_y << std::endl;

    m_object->setVelocity(velocity);
    m_object->setAngularVelocity(angularVelocity);

    Controller::move();

}

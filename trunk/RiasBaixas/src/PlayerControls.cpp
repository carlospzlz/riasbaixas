#include <PlayerControls.h>


//const float PlayerControls::m_highSpeedZ = 0.6;
//const float PlayerControls::s_highSpeedX = 0.2;
//const float PlayerControls::s_emersionHigh = 0.2;
//const float PlayerControls::s_lateralStreamForce = 0.03;
//const float PlayerControls::s_amplitudeBouncing = 0.008;
//const float PlayerControls::s_frecuencyBouncing = M_PI/60;

PlayerControls::PlayerControls()
{
    m_left = false;
    m_right = false;
    m_speedUp = false;
    m_floating = true;
    m_ticksBouncing = 0;

}

void PlayerControls::move(ngl::Transformation &_transform, ngl::Vec4 &_velocity, ngl::Vec4 &_angularVelocity, degreesOfFreedom &_dof)
{
    //std::cout << "PlayerControls: player controlling [" << m_left << " "<< m_speedUp << " "<< m_right << "]"<< std::endl;

    //m_acceleration = ngl::Vec4(CONTROLLER_MOTOR_FORCE/m_object->getMass(),CONTROLLER_MOTOR_FORCE/m_object->getMass(),CONTROLLER_MOTOR_FORCE/m_object->m_getMass(),1);

    float maxSpeed;
    if (m_speedUp)
        maxSpeed = m_highSpeedZ;
    else
        maxSpeed = m_regularSpeed;

    ngl::Vec4 position = _transform.getPosition();
    ngl::Vec4 rotation = _transform.getRotation();

    //MOVING IN X
    if (m_left && !m_right)
    {
        //comber left
         _velocity.m_x += -m_acceleration.m_x;
         _angularVelocity.m_y = m_angularVelocity;
         _angularVelocity.m_x = -m_angularVelocity;
        }

    if (m_right && !m_left)
    {
        //comber right
        _velocity.m_x += m_acceleration.m_x;
        _angularVelocity.m_y = -m_angularVelocity;
        _angularVelocity.m_x = m_angularVelocity;
    }


    if (rotation.m_x > m_maxCamber || rotation.m_x < -m_maxCamber)
        _angularVelocity.m_x = 0;
    if (rotation.m_y > 90+ m_maxCamber || (rotation.m_y < 90 -m_maxCamber))
        _angularVelocity.m_y = 0;


    //recover velocity and comber

    if ((!m_left && !m_right) || (m_left && m_right))
    {
        //recover velocity

        if (_velocity.m_x > m_acceleration.m_x)
            _velocity.m_x -= m_acceleration.m_x;
        else if (_velocity.m_x < -m_acceleration.m_x)
            _velocity.m_x += m_acceleration.m_x;
        else
            _velocity.m_x = 0;

         //recover comber in Y
         if (rotation.m_y < 90)
             _angularVelocity.m_y = m_angularVelocity;
         else if (rotation.m_y > 90)
             _angularVelocity.m_y = -m_angularVelocity;
         else
             _angularVelocity.m_y = 0;

         //recover comber in X
         if (rotation.m_x > 0)
             _angularVelocity.m_x = -m_angularVelocity;
         else if (rotation.m_x < 0)
             _angularVelocity.m_x = m_angularVelocity;
         else
             _angularVelocity.m_x = 0;
    }

    //campling velocity in x
    _velocity.m_x = std::min(_velocity.m_x, m_highSpeedX);
    _velocity.m_x = std::max(_velocity.m_x, -m_highSpeedX);

    //DECIDE IF LATERAL STREAM FORCES OR THE BOAT STOP IN DRY
    //if ( (_transform.getPosition().m_x<-SEA_WIDTH/2.0 && m_left) || (_transform.getPosition().m_x>SEA_WIDTH/2.0 && m_right) || (m_left && m_right))
    //    _vel.m_x = 0;
    if ( position.m_x < -SEA_WIDTH/2.0 )
       _velocity.m_x += m_lateralStreamForce;
    if ( position.m_x > SEA_WIDTH/2.0 )
       _velocity.m_x -= m_lateralStreamForce;


    //MOVING IN Y
    //State machine
    if (m_floating)
    {
        _velocity.m_y = floatingVelocity();
        if (m_speedUp)
        {
            m_floating = false;
            m_emerging = true;
        }
    }

    if (m_emerging)
    {
        _velocity.m_y += m_acceleration.m_y;
        _velocity.m_y = std::min(_velocity.m_y, m_regularSpeed);
        if (position.m_y > m_emersionHeight)
        {
            m_emerging = false;
            m_bouncing = true;
            m_ticksBouncing = 0;
            _velocity.m_y = 0;
        }
        if (!m_speedUp)
        {
            m_emerging = false;
            m_immersing = true;
        }
    }

    if (m_bouncing)
    {
        _velocity.m_y = m_bouncingAmplitude*std::sin(m_bouncingFrequency*m_ticksBouncing);
         ++m_ticksBouncing;
        if (!m_speedUp)
        {
            m_bouncing = false;
            m_immersing = true;
        }
    }

    if (m_immersing)
    {
       _velocity.m_y -= m_frictionForce;
       _velocity.m_y = std::max(_velocity.m_y, -m_regularSpeed);
       if (position.m_y<SEA_FLOATING_HIGH)
       {
           m_immersing = false;
           m_floating = true;
           resetFloatingVelocity();
           _velocity.m_y = 0;
       }
    }

    //MOVING IN Z

    //accelerating
    if (m_speedUp || _velocity.m_z < m_regularSpeed)
        _velocity.m_z -= m_acceleration.m_z;
    else
        _velocity.m_z += m_acceleration.m_z;

    //velocity.m_z = std::max(std::abs(velocity.m_z), maxSpeed);
    _velocity.m_z = -std::min(std::abs(_velocity.m_z), maxSpeed);

    //std::cout << "Player Controls: state: { " <<m_floating<< " " << m_emerging << " " << m_bouncing << " " << m_immersing << " } high "<< position.m_y << std::endl;

    _transform.addPosition(_velocity);
    _transform.addRotation(_angularVelocity);

}

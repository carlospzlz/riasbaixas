#include <PlayerControls.h>


PlayerControls::PlayerControls()
{
    m_left = false;
    m_right = false;
    m_speedUp = false;
    m_floating = true;
    m_ticksFloating = 0;
    m_ticksBouncing = 0;
}

void PlayerControls::move(ngl::Transformation &_transform, float _mass, ngl::Vec4 &_vel, float &_maxSpeed,
                  ngl::Vec4 &_angVel, float _maxCamber, const degreesOfFreedom &_dof, bool _jumping)
{
    std::cout << "PlayerControls: player controlling [" << m_left << " "<< m_speedUp << " "<< m_right << "]"<< std::endl;

    assert(_mass!=0);
    m_acceleration = ngl::Vec4(CONTROLLER_MOTOR_FORCE/_mass,CONTROLLER_MOTOR_FORCE/_mass,CONTROLLER_MOTOR_FORCE/_mass,1);

    _maxSpeed = m_speedUp ? (float)PLAYERCONTROLS_HIGHSPEED : (float)CONTROLLER_SPEED;

    if (_jumping)
        std::cout << "it jumps" << std::endl;
    else
    {

        //MOVING IN X

        if (m_left && !m_right)
        {
            //comber left
            _vel.m_x += -m_acceleration.m_x;
            _angVel.m_y = CONTROLLER_ANGULAR_VELOCITY;
            _angVel.m_x = -CONTROLLER_ANGULAR_VELOCITY;
        }

        if (m_right && !m_left)
        {
            //comber right
            _vel.m_x += m_acceleration.m_x;
            _angVel.m_y = -CONTROLLER_ANGULAR_VELOCITY;
            _angVel.m_x = CONTROLLER_ANGULAR_VELOCITY;
        }


        if ((_transform.getRotation().m_x > _maxCamber) || (_transform.getRotation().m_x < -_maxCamber))
            _angVel.m_x = 0;
        if ((_transform.getRotation().m_y > 90+_maxCamber) || (_transform.getRotation().m_y < 90-_maxCamber))
            _angVel.m_y = 0;


        //recover velocity and comber

        if ((!m_left && !m_right) || (m_left && m_right))
        {
            //recover velocity

            if (_vel.m_x > m_acceleration.m_x)
                _vel.m_x -= m_acceleration.m_x;
            else if (_vel.m_x < -m_acceleration.m_x)
                _vel.m_x += m_acceleration.m_x;
            else
                _vel.m_x = 0;

            //recover comber in Y
            if (_transform.getRotation().m_y < 90)
                _angVel.m_y = CONTROLLER_ANGULAR_VELOCITY;
            else if (_transform.getRotation().m_y > 90)
                _angVel.m_y = -CONTROLLER_ANGULAR_VELOCITY;
            else
                _angVel.m_y = 0;

            //recover comber in X
            if (_transform.getRotation().m_x > 0)
                _angVel.m_x = -CONTROLLER_ANGULAR_VELOCITY;
            else if (_transform.getRotation().m_x < 0)
                _angVel.m_x = CONTROLLER_ANGULAR_VELOCITY;
            else
                _angVel.m_x = 0;
        }

        //campling velocity in x
        _vel.m_x = std::min(_vel.m_x, (float)PLAYERCONTROLS_HIGHSPEED_X);
        _vel.m_x = std::max(_vel.m_x, (float)-PLAYERCONTROLS_HIGHSPEED_X);

        //DECIDE IF LATERAL STREAM FORCES OR THE BOAT STOP IN DRY
        //if ( (_transform.getPosition().m_x<-SEA_WIDTH/2.0 && m_left) || (_transform.getPosition().m_x>SEA_WIDTH/2.0 && m_right) || (m_left && m_right))
        //    _vel.m_x = 0;
        if ( (_transform.getPosition().m_x<-SEA_WIDTH/2.0) )
            _vel.m_x += PLAYERCONTROLS_LATERAL_STREAM_FORCE;
        if ( (_transform.getPosition().m_x>SEA_WIDTH/2.0) )
            _vel.m_x -= PLAYERCONTROLS_LATERAL_STREAM_FORCE;


        //MOVING IN Y

        if (m_floating)
            _vel.m_y = floatingVelocity();
            //{
        //    _vel.m_y = PLAYERCONTROLS_AMPLITUDE_FLOATING*-std::cos(PLAYERCONTROLS_FRECUENCY*m_ticksFloating);
        //    ++m_ticksFloating;
        //}

        if (m_speedUp && !m_bouncing )
        {
            m_floating = false;
            _vel.m_y += m_acceleration.m_y;
        }

        if (m_speedUp && _transform.getPosition().m_y >= PLAYERCONTROLS_EMERSION_HIGH && !m_bouncing) //&& _vel.m_z >= PLAYERCONTROLS_MAX_VELOCITY_Z
        {
            _vel.m_y = 0;
            m_bouncing = true;
            m_ticksBouncing = 0;
        }

        if (m_bouncing)
        {
            _vel.m_y = PLAYERCONTROLS_AMPLITUDE_BOUNCING*std::cos(PLAYERCONTROLS_FRECUENCY_BOUNCING*m_ticksBouncing);
             ++m_ticksBouncing;
            if (m_ticksBouncing*PLAYERCONTROLS_FRECUENCY_BOUNCING>M_PI)
                m_ticksBouncing=0;
        }

        if (!m_speedUp && m_bouncing)
        {
            m_bouncing = false;
        }

        if (!m_speedUp && !m_floating)
            _vel.m_y -= CONTROLLER_FRICTION_FORCE;

        if (!m_speedUp && !m_floating && _transform.getPosition().m_y<=SEA_FLOATING_HIGH)
        {
           m_floating = true;
           //m_ticksFloating = 0;
           resetFloatingVelocity();
        }        


        //MOVING IN Z

        //accelerating
        if (m_speedUp)
            _vel.m_z -= m_acceleration.m_z;
        else
            _vel.m_z += m_acceleration.m_z;

        _vel.m_z = std::max(std::abs(_vel.m_z), _maxSpeed);
        _vel.m_z = -std::min(std::abs(_vel.m_z), _maxSpeed);
    }

    //std::cout << "Player Controls: state: { floating " <<m_floating<<" ("<< m_ticksFloating <<"), bouncing "<<m_bouncing<<" (" << m_ticksBouncing <<") }" << std::endl;

    _transform.addPosition(_vel);
    _transform.addRotation(_angVel);

}

#include "Diagonal.h"
#include "Sea.h"

Diagonal::Diagonal()
{
    m_angle = 0;
    m_quadrant = 1;
    m_ticksFloating = 0;
}

void Diagonal::move(ngl::Transformation &_transform, float _mass, ngl::Vec4 &_vel, float &_maxSpeed,
                  ngl::Vec4 &_angVel, float _maxCamber, const degreesOfFreedom &_dof, bool _jumping)
{
    m_acceleration = ngl::Vec4(CONTROLLER_MOTOR_FORCE/_mass, CONTROLLER_MOTOR_FORCE/_mass, CONTROLLER_MOTOR_FORCE/_mass, 1);

    m_angle = _transform.getRotation().m_y;
    m_angle = m_angle % 360;

    //FIRST QUADRANT
    if (m_quadrant == 1)
    {
        if (m_angle > 45-CONTROLLER_ANGULAR_VELOCITY && m_angle < 45+CONTROLLER_ANGULAR_VELOCITY)
            _angVel.m_y = 0;
        else if (m_angle > 45 && m_angle <= 135)
        {
            _angVel.m_y = -CONTROLLER_ANGULAR_VELOCITY;
            _angVel.m_x = CONTROLLER_ANGULAR_VELOCITY;
        }
        else
        {
            _angVel.m_y = CONTROLLER_ANGULAR_VELOCITY;
            _angVel.m_x = -CONTROLLER_ANGULAR_VELOCITY;
        }
        _vel.m_x += m_acceleration.m_x;
        _vel.m_z -= m_acceleration.m_z;
    }

    //SECOND QUADRANT
    if (m_quadrant == 2)
    {
        if (m_angle > 135-CONTROLLER_ANGULAR_VELOCITY && m_angle < 135+CONTROLLER_ANGULAR_VELOCITY)
            _angVel.m_y = 0;
        else if (m_angle > 135 && m_angle < 315)
        {
            _angVel.m_y = -CONTROLLER_ANGULAR_VELOCITY;
            _angVel.m_x = CONTROLLER_ANGULAR_VELOCITY;
        }
        else
        {
            _angVel.m_y = CONTROLLER_ANGULAR_VELOCITY;
            _angVel.m_x = -CONTROLLER_ANGULAR_VELOCITY;
        }
        _vel.m_x -= m_acceleration.m_x;
        _vel.m_z -= m_acceleration.m_z;
    }

    //THIRD QUADRANT
    if (m_quadrant == 3)
    {
        if (m_angle > 225-CONTROLLER_ANGULAR_VELOCITY && m_angle < 225+CONTROLLER_ANGULAR_VELOCITY)
            _angVel.m_y = 0;
        else if (m_angle > 45 && m_angle < 225)
        {
            _angVel.m_y = CONTROLLER_ANGULAR_VELOCITY;
            _angVel.m_x = -CONTROLLER_ANGULAR_VELOCITY;
        }
        else
        {
            _angVel.m_y = -CONTROLLER_ANGULAR_VELOCITY;
            _angVel.m_x = CONTROLLER_ANGULAR_VELOCITY;
        }
        _vel.m_x -= m_acceleration.m_x;
        _vel.m_z += m_acceleration.m_z;
    }

    //FORTH QUADRANT
    if (m_quadrant == 4)
    {
        if (m_angle > 315-CONTROLLER_ANGULAR_VELOCITY && m_angle < 315+CONTROLLER_ANGULAR_VELOCITY)
            _angVel.m_y = 0;
        else if (m_angle > 135 && m_angle < 315)
        {
            _angVel.m_y = CONTROLLER_ANGULAR_VELOCITY;
            _angVel.m_x = -CONTROLLER_ANGULAR_VELOCITY;
        }
        else
        {
            _angVel.m_y = -CONTROLLER_ANGULAR_VELOCITY;
            _angVel.m_x = CONTROLLER_ANGULAR_VELOCITY;
        }
        _vel.m_x += m_acceleration.m_x;
        _vel.m_z += m_acceleration.m_z;
    }

    //CLAMPING TO MAXIMUM ROTATION IN X
    if (_transform.getRotation().m_x>CONTROLLER_CAMBER || _transform.getRotation().m_x<-CONTROLLER_CAMBER )
        _angVel.m_x = 0;

    //RECOVER CAMBER IN X
    if (_angVel.m_y == 0)
    {
        if (_transform.getRotation().m_x<-CONTROLLER_ANGULAR_VELOCITY)
               _angVel.m_x = CONTROLLER_ANGULAR_VELOCITY;
        else if ( _transform.getRotation().m_x>CONTROLLER_ANGULAR_VELOCITY)
                _angVel.m_x = -CONTROLLER_ANGULAR_VELOCITY;
        else
            _angVel.m_x = 0;
    }

    //COLLISIONS WITH SEA LIMITS (MODIFY THIS WHEN ADDING DEGREES FO FREEDOM)
    if (_transform.getPosition().m_x > SEA_WIDTH/2.0)
    {
        if (m_quadrant == 1)
            m_quadrant = 2;
        if (m_quadrant == 4)
            m_quadrant = 3;
    }

    if (_transform.getPosition().m_x < -SEA_WIDTH/2.0)
    {
        if (m_quadrant == 2)
            m_quadrant = 1;
        if (m_quadrant == 3)
            m_quadrant = 4;
    }

    //CLAMPING

    _vel.m_z = std::max(_vel.m_z, (float)-CONTROLLER_SPEED);
    _vel.m_z = std::min(_vel.m_z, (float)CONTROLLER_SPEED);

    _vel.m_x = std::max(_vel.m_x, (float)-CONTROLLER_SPEED);
    _vel.m_x = std::min(_vel.m_x, (float)CONTROLLER_SPEED);

    //FLOATING MOVEMENT IN Y

    _vel.m_y = floatingVelocity();

    //std::cout << "DIAGONAL: { quadrant: " << m_quadrant << ", angle: " << m_angle << "}" << std::endl;

    _transform.addPosition(_vel);
    _transform.addRotation(_angVel);


}

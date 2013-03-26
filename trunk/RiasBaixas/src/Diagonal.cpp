#include "Diagonal.h"
#include "Sea.h"

Diagonal::Diagonal()
{
    m_angle = 0;
    m_quadrant = 1;
}

void Diagonal::move(ngl::Transformation &_transform, ngl::Vec4 &_velocity, ngl::Vec4 &_angularVelocity, degreesOfFreedom &_dof)
{
    ngl::Vec4 rotation = _transform.getRotation();

    m_angle = rotation.m_y;
    m_angle = m_angle % 360;

    //FIRST QUADRANT
    if (m_quadrant == 1)
    {
        if (m_angle > 45-m_angularVelocity && m_angle < 45+m_angularVelocity)
            _angularVelocity.m_y = 0;
        else if (m_angle > 45 && m_angle <= 135)
        {
            _angularVelocity.m_y = -m_angularVelocity;
            _angularVelocity.m_x = m_angularVelocity;
        }
        else
        {
            _angularVelocity.m_y = m_angularVelocity;
            _angularVelocity.m_x = -m_angularVelocity;
        }
        _velocity.m_x += m_acceleration.m_x;
        _velocity.m_z -= m_acceleration.m_z;
    }

    //SECOND QUADRANT
    if (m_quadrant == 2)
    {
        if (m_angle > 135-m_angularVelocity && m_angle < 135+m_angularVelocity)
            _angularVelocity.m_y = 0;
        else if (m_angle > 135 && m_angle < 315)
        {
            _angularVelocity.m_y = -m_angularVelocity;
            _angularVelocity.m_x = m_angularVelocity;
        }
        else
        {
            _angularVelocity.m_y = m_angularVelocity;
            _angularVelocity.m_x = -m_angularVelocity;
        }
        _velocity.m_x -= m_acceleration.m_x;
        _velocity.m_z -= m_acceleration.m_z;
    }

    //THIRD QUADRANT
    if (m_quadrant == 3)
    {
        if (m_angle > 225-m_angularVelocity && m_angle < 225+m_angularVelocity)
            _angularVelocity.m_y = 0;
        else if (m_angle > 45 && m_angle < 225)
        {
            _angularVelocity.m_y = m_angularVelocity;
            _angularVelocity.m_x = -m_angularVelocity;
        }
        else
        {
            _angularVelocity.m_y = -m_angularVelocity;
            _angularVelocity.m_x = m_angularVelocity;
        }
        _velocity.m_x -= m_acceleration.m_x;
        _velocity.m_z += m_acceleration.m_z;
    }

    //FORTH QUADRANT
    if (m_quadrant == 4)
    {
        if (m_angle > 315-m_angularVelocity && m_angle < 315+m_angularVelocity)
            _angularVelocity.m_y = 0;
        else if (m_angle > 135 && m_angle < 315)
        {
            _angularVelocity.m_y = m_angularVelocity;
            _angularVelocity.m_x = -m_angularVelocity;
        }
        else
        {
            _angularVelocity.m_y = -m_angularVelocity;
            _angularVelocity.m_x = m_angularVelocity;
        }
        _velocity.m_x += m_acceleration.m_x;
        _velocity.m_z += m_acceleration.m_z;
    }

    //CLAMPING TO MAXIMUM ROTATION IN X
    if (rotation.m_x>m_maxCamber || rotation.m_x<-m_maxCamber )
        _angularVelocity.m_x = 0;

    //RECOVER CAMBER IN X
    if (_angularVelocity.m_y == 0)
    {
        if (rotation.m_x < -m_angularVelocity)
               _angularVelocity.m_x = m_angularVelocity;
        else if ( rotation.m_x > m_angularVelocity)
                _angularVelocity.m_x = -m_angularVelocity;
        else
            _angularVelocity.m_x = 0;
    }

    //COLLISIONS WITH SEA LIMITS (MODIFY THIS WHEN ADDING DEGREES FO FREEDOM)
    if (!_dof.right)
    {
        if (m_quadrant == 1)
            m_quadrant = 2;
        if (m_quadrant == 4)
            m_quadrant = 3;
    }

    if (!_dof.left)
    {
        if (m_quadrant == 2)
            m_quadrant = 1;
        if (m_quadrant == 3)
            m_quadrant = 4;
    }

    //CLAMPING

    _velocity.m_z = std::max(_velocity.m_z, -m_regularSpeed);
    _velocity.m_z = std::min(_velocity.m_z, m_regularSpeed);

    _velocity.m_x = std::max(_velocity.m_x, -m_regularSpeed);
    _velocity.m_x = std::min(_velocity.m_x, m_regularSpeed);

    //FLOATING MOVEMENT IN Y

    _velocity.m_y = floatingVelocity();

    //std::cout << "DIAGONAL: { quadrant: " << m_quadrant << ", angle: " << m_angle << "}" << std::endl;

    _transform.addPosition(_velocity);
    _transform.addRotation(_angularVelocity);
}

#include "Vertical.h"

Vertical::Vertical()
{
    m_goingForward = false;
}

void Vertical::move(ngl::Transformation &_transform, ngl::Vec4 &_velocity, ngl::Vec4 &_angularVelocity, degreesOfFreedom &_dof)
{

    if (m_goingForward)
        _velocity.m_z -= s_motorForce;
    else
        _velocity.m_z += s_motorForce;

    _velocity.m_z = std::max(_velocity.m_z, -s_regularSpeed);
    _velocity.m_z = std::min(_velocity.m_z, s_regularSpeed);

    //Friction force in Z
    if (_velocity.m_x < -s_frictionForce)
        _velocity.m_x += s_frictionForce;
    else if (_velocity.m_x > s_frictionForce)
        _velocity.m_x -= s_frictionForce;
    else
        _velocity.m_x = 0;

    //Floating in Y
    _velocity.m_y = floatingVelocity();

    _transform.addPosition(_velocity);

}

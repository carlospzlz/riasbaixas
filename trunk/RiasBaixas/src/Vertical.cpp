#include "Vertical.h"

Vertical::Vertical()
{
    m_goingForward = false;
}

void Vertical::move(ngl::Transformation &_transform, float _mass, ngl::Vec4 &_vel, float &_maxSpeed,
               ngl::Vec4 &_angVel, float _maxCamber, const degreesOfFreedom &_dof, bool _jumping)
{

    m_acceleration = ngl::Vec4(CONTROLLER_MOTOR_FORCE/_mass, CONTROLLER_MOTOR_FORCE/_mass, CONTROLLER_MOTOR_FORCE/_mass, 1);

    if (m_goingForward)
        _vel.m_z -= CONTROLLER_MOTOR_FORCE;
    else
        _vel.m_z += CONTROLLER_MOTOR_FORCE;

    _vel.m_z = std::max(_vel.m_z, (float)-CONTROLLER_SPEED);
    _vel.m_z = std::min(_vel.m_z, (float)CONTROLLER_SPEED);

    //Friction force in Z
    if (_vel.m_x < -CONTROLLER_FRICTION_FORCE)
        _vel.m_x += CONTROLLER_FRICTION_FORCE;
    else if (_vel.m_x > CONTROLLER_FRICTION_FORCE)
        _vel.m_x -= CONTROLLER_FRICTION_FORCE;
    else
        _vel.m_x = 0;

    //Floating in Y
    _vel.m_y = floatingVelocity();

    _transform.addPosition(_vel);

}

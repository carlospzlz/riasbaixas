#include "Floating.h"


void Floating::move(ngl::Transformation &_transform, float _mass, ngl::Vec4 &_vel, float &_maxSpeed,
                  ngl::Vec4 &_angVel, float _maxCamber, const degreesOfFreedom &_dof, bool _jumping)
{
    _vel.m_y = floatingVelocity();

    m_acceleration = ngl::Vec4(CONTROLLER_FRICTION_FORCE/_mass, CONTROLLER_FRICTION_FORCE/_mass, CONTROLLER_FRICTION_FORCE/_mass, 1);

    //FRICTION FORCE IN CASE IT'S MOVING

    //in X
    if (_vel.m_x < -m_acceleration.m_x)
        _vel.m_x += m_acceleration.m_x;
    else if (_vel.m_x > m_acceleration.m_x)
        _vel.m_x -= m_acceleration.m_x;
    else
        _vel.m_x = 0;

    //in Z
    if (_vel.m_z < -m_acceleration.m_z)
        _vel.m_z += m_acceleration.m_z;
    else if (_vel.m_z > m_acceleration.m_z)
        _vel.m_z -= m_acceleration.m_z;
    else
        _vel.m_z = 0;

    _transform.addPosition(_vel);

}

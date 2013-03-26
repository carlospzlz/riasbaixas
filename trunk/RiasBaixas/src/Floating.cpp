#include "Floating.h"


void Floating::move(ngl::Transformation &_transform, ngl::Vec4 &_velocity, ngl::Vec4 &_angularVelocity, degreesOfFreedom &_dof)
{

    //Unused variables for floating
    (void)_dof;

    _velocity.m_y = floatingVelocity();

    //FRICTION FORCE IN CASE IT'S MOVING

    //in X
    if (_velocity.m_x < -m_acceleration.m_x)
        _velocity.m_x += m_acceleration.m_x;
    else if (_velocity.m_x > m_acceleration.m_x)
        _velocity.m_x -= m_acceleration.m_x;
    else
        _velocity.m_x = 0;

    //in Z
    if (_velocity.m_z < -m_acceleration.m_z)
        _velocity.m_z += m_acceleration.m_z;
    else if (_velocity.m_z > m_acceleration.m_z)
        _velocity.m_z -= m_acceleration.m_z;
    else
        _velocity.m_z = 0;

    _transform.addPosition(_velocity);
    _transform.addRotation(_angularVelocity);

    std::cout << "HEREEE" << m_acceleration.m_z << std::endl;

}

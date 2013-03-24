#include <Horizontal.h>

Horizontal::Horizontal()
{
    m_goingRight = true;
}

void Horizontal::move(ngl::Transformation &_transform, ngl::Vec4 &_velocity, ngl::Vec4 &_angularVelocity, degreesOfFreedom &_dof)
{

    if (m_goingRight)
        _velocity.m_x += m_acceleration.m_x;
    else
        _velocity.m_x -= m_acceleration.m_x;

    _velocity.m_x = std::max(_velocity.m_x, -s_regularSpeed);
    _velocity.m_x = std::min(_velocity.m_x, s_regularSpeed);

    if (!_dof.right)
        m_goingRight = false;
    if (!_dof.left)
        m_goingRight = true;

    //Friction force in Z
    if (_velocity.m_z < -s_frictionForce)
        _velocity.m_z += s_frictionForce;
    else if (_velocity.m_z > s_frictionForce)
        _velocity.m_z -= s_frictionForce;
    else
        _velocity.m_z = 0;

    //Floating in Y
    _velocity.m_y = floatingVelocity();

    _transform.addPosition(_velocity);

    //std::cout << "Horizontal: Velocity.m_x = " << m_object->getVelocity().m_x << std::endl;

}

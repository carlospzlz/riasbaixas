#include <Behaviour.h>


Behaviour::Behaviour()
{
    m_acceleration = ngl::Vec4(0,0,0,0);
    m_ticksFloating = rand() % 100;//rand();// % (int) M_PI/m_floatingFrequency;
}

void Behaviour::setAcceleration(float _mass)
{
    assert(_mass!=0);
    m_acceleration = ngl::Vec4(m_motorForce/_mass,m_motorForce/_mass,m_motorForce/_mass,1);
}

float Behaviour::floatingVelocity()
{
    float yVel = m_floatingAmplitude*-std::cos(m_floatingFrequency*m_ticksFloating);
    ++m_ticksFloating;
    return yVel;
}

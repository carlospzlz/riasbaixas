#include <Controller.h>

Controller::Controller()
{
    m_acceleration = ngl::Vec4(0,0,0,0);
    float frequency  = CONTROLLER_FLOATING_FRECUENCY;
    m_ticksFloating = rand() % (int) M_PI/frequency;
    std::cout << " FLOATING TICKS " << m_ticksFloating << " " << (int)M_PI << " " << (float)CONTROLLER_FLOATING_FRECUENCY << std::endl;
}

void Controller::move(ngl::Transformation &_transform, float _mass, ngl::Vec4 &_vel, float &_maxSpeed,
                              ngl::Vec4 &_angVel, float _maxCamber, const degreesOfFreedom &_dof, bool _jumping)
{
    std::cout << "This controller has undefined movement" << std::endl;
}

float Controller::floatingVelocity()
{
    float yVel = CONTROLLER_FLOATING_AMPLITUDE*-std::cos(CONTROLLER_FLOATING_FRECUENCY*m_ticksFloating);
    ++m_ticksFloating;
    return yVel;
}

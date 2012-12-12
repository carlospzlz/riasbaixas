#include <Controller.h>

Controller::Controller()
{
    m_acceleration = ngl::Vec4(0,0,0,0);
    float frequency  = CONTROLLER_FLOATING_FRECUENCY;
    m_ticksFloating = rand() % (int) M_PI/frequency;
}

void Controller::setControlledObject(Object *_obj)
{
    m_object = _obj;
    assert(m_object->getMass()!=0);
    m_acceleration = ngl::Vec4(CONTROLLER_MOTOR_FORCE/m_object->getMass(),CONTROLLER_MOTOR_FORCE/m_object->getMass(),CONTROLLER_MOTOR_FORCE/m_object->getMass(),1);
}

void Controller::move()
{
    //std::cout << "This controller has undefined movement" << std::endl;
    m_object->setPreviousPos(m_object->getPosition());
    m_object->setPreviousRot(m_object->getRotation());
    m_object->setPosition(m_object->getPosition()+m_object->getVelocity());
    m_object->setRotation(m_object->getRotation()+m_object->getAngularVelocity());

}

float Controller::floatingVelocity()
{
    float yVel = CONTROLLER_FLOATING_AMPLITUDE*-std::cos(CONTROLLER_FLOATING_FRECUENCY*m_ticksFloating);
    ++m_ticksFloating;
    return yVel;
}

#include <Behaviour.h>


//const float Behaviour::s_floatingAmplitude = 0.008;
//const float Behaviour::s_floatingFrequency = M_PI/40;

//const float Behaviour::s_frictionForce = 0.001;
//const float Behaviour::s_regularSpeed = 0.1;
//const float Behaviour::s_motorForce = 0.005;
//const float Behaviour::s_angularVelocity = 2;
//const float Behaviour::s_camber = 30;

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

//void Controller::setControlledObject(Object *_obj)
//{
//    m_object = _obj;
//    assert(m_object->getMass()!=0);
//    m_acceleration = ngl::Vec4(CONTROLLER_MOTOR_FORCE/m_object->getMass(),CONTROLLER_MOTOR_FORCE/m_object->getMass(),CONTROLLER_MOTOR_FORCE/m_object->getMass(),1);
//}

//void Behaviour::loadParameters(std::string configFile)
//{
//    std::cout << "loading paremeters..." << std::endl;
//}

//void Behaviour::move(ngl::Transformation &_transform, float _mass, float _camber, ngl::Vec4 _velocity, ngl::Vec4 _angVelocity)
//{
//    //std::cout << "This controller has undefined movement" << std::endl;
//    m_object->setPreviousPos(m_object->getPosition());
//    m_object->setPreviousRot(m_object->getRotation());
//    m_object->setPosition(m_object->getPosition()+m_object->getVelocity());
//    m_object->setRotation(m_object->getRotation()+m_object->getAngularVelocity());

//}

float Behaviour::floatingVelocity()
{
    float yVel = m_floatingAmplitude*-std::cos(m_floatingFrequency*m_ticksFloating);
    ++m_ticksFloating;
    return yVel;
}

#include "Predator.h"


Predator::Predator()
{
    PlayerControls *myPlayerControls = new PlayerControls();
    Parser *myParser = new TXTParser();
    myParser->loadPlayerControlsParameters(myPlayerControls);
    //THIS BLOODY LINEE, IF ACCELERATION IS 0, THERE IS NO MOVEMENT
    myPlayerControls->setAcceleration(1);
    m_controls = myPlayerControls;
    //m_controls->setSpeedUp(true);
    delete myParser;
}

void Predator::move(ngl::Transformation &_transform, ngl::Vec4 &_velocity, ngl::Vec4 &_angularVelocity, degreesOfFreedom &_dof)
{

    int stride = 1;

    if (_transform.getPosition().m_z>m_prey->getPosition().m_z)
        m_controls->setSpeedUp(true);
    else
        m_controls->setSpeedUp(false);

    if (_transform.getPosition().m_x<m_prey->getPosition().m_x-stride)
    {
        m_controls->setRight(true);
        m_controls->setLeft(false);
    }
    else if (_transform.getPosition().m_x>m_prey->getPosition().m_x+stride)
    {
        m_controls->setRight(false);
        m_controls->setLeft(true);
    }
    else
    {
        m_controls->setRight(false);
        m_controls->setLeft(false);
    }

    //Delegation, the PlayerControls move the object ...
    m_controls->move(_transform, _velocity, _angularVelocity, _dof);

}

#include "PoliceBoat.h"

PoliceBoat::PoliceBoat()
{
    setType(ot_policeBoat);
    setPrimName("teapot");
    setPosition(ngl::Vec4(0,0.3,0,1));
    setRotation(ngl::Vec4(0,90,0,1));
    setVelocity(ngl::Vec4(0,0,0,1));
    m_chasing = false;
}

void PoliceBoat::collisionEvent(Object& _o)
{
    (void)_o;
    //reduce amount of load
}

void PoliceBoat::update()
{
    if (!m_chasing && m_speedboat->getPosition().m_z<getPosition().m_z)
    {
        Predator *myPredator = new Predator();
        myPredator->setPrey(m_speedboat);
        setBehaviour(myPredator);
        m_chasing = true;
    }

    if (m_behaviour)
    {
        m_previousTransform.setPosition(m_transform.getPosition());
        m_previousTransform.setRotation(m_transform.getRotation());
        m_behaviour->move(m_transform, m_velocity, m_angularVelocity, m_degreesOfFreedom);
    }
    else
        std::cout << "PoliceBoat: No behaviour defined!" << std::endl;
}

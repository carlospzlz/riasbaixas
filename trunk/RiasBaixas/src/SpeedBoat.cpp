#include "SpeedBoat.h"
#include <iostream>
#include <SDL/SDL.h>
#include <math.h>


SpeedBoat::SpeedBoat()
{
    setPrimName("teapot");
    setRotation(ngl::Vec3(0,90,0));
}

void SpeedBoat::update(int _currentZ, float _far)
{
    //if currentZ-this.z blah inactive or active...
    std::cout << "SpeedBoat updating!" << std::endl;
    //if active move
    update(_currentZ, _far);
    m_controller->move(m_position, m_rotation, m_velocity, m_maxSpeed, m_jumping, m_degreesOfFreedom);
}

void SpeedBoat::collisionEvent(Object _o)
{
    //reduce amount of load
}

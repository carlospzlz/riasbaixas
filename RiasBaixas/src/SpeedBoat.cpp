#include "SpeedBoat.h"
#include <iostream>
#include <math.h>


SpeedBoat::SpeedBoat()
{
    setType(ot_speedBoat);
    setPrimName("teapot");
    setPosition(ngl::Vec4(0,0.3,0,1));
    setRotation(ngl::Vec4(0,90,0,1));
    setVelocity(ngl::Vec4(0,0,0,1));
}

void SpeedBoat::collisionEvent(Object& _o)
{
    std::cout << "Speedboat collided with " << _o.getType() << std::endl;
    //reduce amount of load
}

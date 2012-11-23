#include "SpeedBoat.h"
#include <iostream>
#include <SDL/SDL.h>
#include <math.h>


SpeedBoat::SpeedBoat()
{
    setType(ot_speedBoat);
    setPrimName("teapot");
    setRotation(ngl::Vec3(0,90,0));
    setVelocity(ngl::Vec3(0.05,0.05,0.05));
}

void SpeedBoat::collisionEvent(Object _o)
{
    //reduce amount of load
}

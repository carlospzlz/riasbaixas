#include "SpeedBoat.h"
#include <iostream>
#include <math.h>


SpeedBoat::SpeedBoat()
{
    setType(ot_speedBoat);
    ngl::Transformation t;
    t.setRotation(0,-90,0);
    t.setScale(0.2,0.2,0.2);
    setMeshInitTransform(t);
    t.reset();
    setPrimName("teapot");
    t.setRotation(0,90,0);
    setPrimInitTransform(t);
    setPosition(ngl::Vec4(0,0.3,0,1));
    //setRotation(ngl::Vec4(0,90,0,1));
    setVelocity(ngl::Vec4(0,0,0,1));
}

void SpeedBoat::collisionEvent(Object& _o)
{
    //reduce amount of load

    Object::collisionEvent(_o);
}

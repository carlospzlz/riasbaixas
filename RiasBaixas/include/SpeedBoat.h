#ifndef SPEEDBOAT_H
#define SPEEDBOAT_H

#include <ngl/Obj.h>
#include <ngl/Transformation.h>
#include <ngl/Vec3.h>
#include <ngl/ShaderLib.h>
#include <ngl/Camera.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/TransformStack.h>
#include <ngl/Material.h>
#include <ngl/Light.h>

#include "Object.h"

#define SPEEDBOAT_SPEED_FACTOR 3
#define SPEEDBOAT_COMBER_STEP 2
#define SPEEDBOAT_COMBER_MAX 20
#define MAX_LOAD 300;

class SpeedBoat : public Object
{
private:
    int m_load;
    //int ticks;

public:
    SpeedBoat();
    ~SpeedBoat() { };
    void setLoad(int _l) { m_load = _l; }
    int getLoad() { return m_load; }

    void collisionEvent(Object &_o);
};

#endif // SPEEDBOAT_H

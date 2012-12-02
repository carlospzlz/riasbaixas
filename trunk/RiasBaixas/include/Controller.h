#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <time.h>
#include <ngl/Vec3.h>
#include <ngl/Transformation.h>
#include "Object.h"
#include "Sea.h"

#define CONTROLLER_FRICTION_FORCE 0.001
#define CONTROLLER_SPEED 0.1
#define CONTROLLER_MOTOR_FORCE 0.005
#define CONTROLLER_FLOATING_AMPLITUDE 0.008
#define CONTROLLER_FLOATING_FRECUENCY M_PI/40
#define CONTROLLER_ANGULAR_VELOCITY 2
#define CONTROLLER_CAMBER 30


class Controller
{

private:
    int m_ticksFloating;

protected:
    Object* m_object;
    ngl::Vec4 m_acceleration;
    float floatingVelocity();
    void resetFloatingVelocity() { m_ticksFloating=0; }

public:
    Controller();
    void setControlledObject(Object* _o);
    bool isActive() { return m_object!=NULL && m_object->isActive(); }
    virtual void move();

};

#endif // CONTROLLER_H

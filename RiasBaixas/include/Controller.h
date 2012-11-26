#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <time.h>
#include <ngl/Vec3.h>
#include <ngl/Transformation.h>
#include "Sea.h"

#define CONTROLLER_FRICTION_FORCE 0.001
#define CONTROLLER_SPEED 0.1
#define CONTROLLER_MOTOR_FORCE 0.005
#define CONTROLLER_FLOATING_AMPLITUDE 0.008
#define CONTROLLER_FLOATING_FRECUENCY M_PI/40
#define CONTROLLER_ANGULAR_VELOCITY 0.5
#define CONTROLLER_CAMBER 30


struct degreesOfFreedom
{
    bool forward;
    bool backward;
    bool left;
    bool right;
    bool up;
    bool down;
};


class Controller
{

private:
    int m_ticksFloating;

protected:
    ngl::Vec4 m_acceleration;

protected:
    float floatingVelocity();
    void resetFloatingVelocity() { m_ticksFloating=0; }

public:
    Controller();
    virtual void move(ngl::Transformation &_transform, float _mass, ngl::Vec4 &_vel, float &_maxSpeed,
                      ngl::Vec4 &_angVel, float _maxCamber, const degreesOfFreedom &_dof, bool _jumping);

};

#endif // CONTROLLER_H

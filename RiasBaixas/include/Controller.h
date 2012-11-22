#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <ngl/Vec3.h>
#include "Sea.h"

struct degreesOfFreedom
{
    bool forward = true;
    bool backward = true;
    bool left = true;
    bool right = true;
    bool up = true;
    bool down = true;
};


class Controller
{

public:
    virtual void move(ngl::Vec3 &_pos, ngl::Vec4 &_rot, ngl::Vec3 &_vel, float &_maxSpeed, const bool _jumping, const degreesOfFreedom _dof);

};

#endif // CONTROLLER_H

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <ngl/Vec3.h>
#include <ngl/Transformation.h>
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
    virtual void move(ngl::Transformation &_transform, ngl::Vec4 &_vel, ngl::Vec4 &_angVel, const degreesOfFreedom _dof, const bool _jumping);

};

#endif // CONTROLLER_H

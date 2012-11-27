#ifndef FLOATING_H
#define FLOATING_H

#include <math.h>
#include "Controller.h"


class Floating : public Controller
{

public:
    virtual void move(ngl::Transformation &_transform, float _mass, ngl::Vec4 &_vel, float &_maxSpeed,
                      ngl::Vec4 &_angVel, float _maxCamber, const degreesOfFreedom &_dof, bool _jumping);

};

#endif // FLOATING_H
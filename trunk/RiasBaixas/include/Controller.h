#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <ngl/Vec3.h>

class Controller
{

public:
    virtual void move(ngl::Vec3 &_pos, ngl::Vec4 &_rot, const ngl::Vec3 &_vel, const int _factorSpeed, const int _combStep, const int _maxComb);

};

#endif // CONTROLLER_H

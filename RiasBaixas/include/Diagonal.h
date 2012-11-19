#ifndef DIAGONAL_H
#define DIAGONAL_H

#include "Controller.h"

class Diagonal : public Controller
{
    void move(ngl::Vec3 &_pos, ngl::Vec4 &_rot, ngl::Vec3 &_vel, const int _factorSpeed, const int _combStep, const int _maxComb);

};

#endif // DIAGONAL_H

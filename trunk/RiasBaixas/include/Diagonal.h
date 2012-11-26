#ifndef DIAGONAL_H
#define DIAGONAL_H

#include "Controller.h"


class Diagonal : public Controller
{

private:
    int m_angle;
    int m_quadrant;
    int m_ticksFloating;

public:
    Diagonal();
    virtual void move(ngl::Transformation &_transform, float _mass, ngl::Vec4 &_vel, float &_maxSpeed,
                      ngl::Vec4 &_angVel, float _maxCamber, const degreesOfFreedom &_dof, bool _jumping);
};
#endif // DIAGONAL_H

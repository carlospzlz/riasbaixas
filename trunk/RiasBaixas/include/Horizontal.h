#ifndef HORIZONTAL_H
#define HORIZONTAL_H

#include "Controller.h"

class Horizontal : public Controller
{

private:
    bool m_goingRight;

public:
    Horizontal();
    virtual void move(ngl::Transformation &_transform, float _mass, ngl::Vec4 &_vel, float &_maxSpeed,
                      ngl::Vec4 &_angVel, float _maxCamber, const degreesOfFreedom &_dof, bool _jumping);

};

#endif // HORIZONTAL_H

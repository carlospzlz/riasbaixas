#ifndef VERTICAL_H
#define VERTICAL_H

#include "Controller.h"

class Vertical : public Controller
{

private:
    bool m_goingForward;

public:
    Vertical();
    virtual void move(ngl::Transformation &_transform, float _mass, ngl::Vec4 &_vel, float &_maxSpeed,
                      ngl::Vec4 &_angVel, float _maxCamber, const degreesOfFreedom &_dof, bool _jumping);

};

#endif // VERTICAL_H

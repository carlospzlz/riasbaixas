#ifndef PLAYERCONTROLS_H
#define PLAYERCONTROLS_H

#include <math.h>
#include "Controller.h"
#include "ngl/Vec3.h"
#include "ngl/Vec4.h"

#define PLAYERCONTROLS_CAMBER 1
#define PLAYERCONTROLS_FRECUENCY M_PI/120
#define PLAYERCONTROLS_AMPLITUDE 0.02

class PlayerControls : public Controller
{
private:
    bool m_left;
    bool m_right;
    bool m_speedUp;
    float m_internalVelInZ;
    int m_ticksJumping;
    int m_ticksFloating;

public:
    PlayerControls();
    void setLeft(bool _pressed);
    void setRight(bool _pressed);
    void setSpeedUp(bool _pressed);
    void move(ngl::Vec3 &_pos, ngl::Vec4 &_rot, const ngl::Vec3 &_vel, const int _factorSpeed, const int _combStep, const int _maxComb);
};

#endif // PLAYERCONTROLS_H

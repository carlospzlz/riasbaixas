#ifndef PLAYERCONTROLS_H
#define PLAYERCONTROLS_H

#include <math.h>
#include "Controller.h"
#include "ngl/Vec3.h"
#include "ngl/Vec4.h"

#define PLAYERCONTROLS_CAMBER 1
#define PLAYERCONTROLS_FRECUENCY M_PI/120
#define PLAYERCONTROLS_AMPLITUDE_FLOATING 0.15
#define PLAYERCONTROLS_AMPLITUDE_BOUNCING 0.5
#define PLAYERCONTROLS_ACELARATION_STEP 0.005
#define PLAYERCONTROLS_DECELARATION_STEP 0.02
#define PLAYERCONTROLS_EMERSION 0.2

class PlayerControls : public Controller
{
private:
    bool m_left;
    bool m_right;
    bool m_speedUp;
    float m_internalVelInZ;
    bool m_floating;
    bool m_bouncing;
    bool m_jumping;
    int m_ticksFloating;
    int m_ticksBouncing;
    int m_ticksJumping;

public:
    PlayerControls();
    void setLeft(bool _pressed);
    void setRight(bool _pressed);
    void setSpeedUp(bool _pressed);
    void move(ngl::Vec3 &_pos, ngl::Vec4 &_rot, const ngl::Vec3 &_vel, const int _factorSpeed, const int _combStep, const int _maxComb);
};

#endif // PLAYERCONTROLS_H

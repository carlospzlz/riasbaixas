#ifndef PLAYERCONTROLS_H
#define PLAYERCONTROLS_H

#include <math.h>
#include "Controller.h"
#include "ngl/Vec3.h"
#include "ngl/Vec4.h"

#define PLAYERCONTROLS_LOWSPEED 0.01
#define PLAYERCONTROLS_HIGHSPEED 0.2
#define PLAYERCONTROLS_CAMBER_STEP 1
#define PLAYERCONTROLS_MAX_CAMBER 30
#define PLAYERCONTROLS_VELOCITY_STEP_X 0.05
#define PLAYERCONTROLS_VELOCITY_STEP_Y 0.001
#define PLAYERCONTROLS_VELOCITY_STEP_Z 0.001
#define PLAYERCONTROLS_MAX_VELOCITY_X 0.3
#define PLAYERCONTROLS_ANGULARVELOCITY_STEP_X 1
#define PLAYERCONTROLS_ANGULARVELOCITY_STEP_Y 1
#define PLAYERCONTROLS_AMPLITUDE_BOUNCING 0.02
#define PLAYERCONTROLS_FRECUENCY M_PI/120
#define PLAYERCONTROLS_EMERSION_HIGH 1


#define PLAYERCONTROLS_AMPLITUDE_FLOATING 0.005

#define PLAYERCONTROLS_ACELARATION_STEP 0.005
#define PLAYERCONTROLS_DECELARATION_STEP 0.02


class PlayerControls : public Controller
{
private:
    bool m_left;
    bool m_right;
    bool m_speedUp;
    bool m_floating;
    bool m_bouncing;
    bool m_jumping;
    int m_ticksFloating;
    int m_ticksBouncing;
    int m_ticksJumping;

public:
    PlayerControls();
    void setLeft(bool _pressed) { m_left = _pressed; }
    void setRight(bool _pressed) { m_right = _pressed; }
    void setSpeedUp(bool _pressed) { m_speedUp = _pressed; }
    void move(ngl::Transformation &_transform, ngl::Vec4 &_vel, ngl::Vec4 &_angVel, const degreesOfFreedom _dof, const bool _jumping);
};

#endif // PLAYERCONTROLS_H

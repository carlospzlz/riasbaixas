#ifndef PLAYERCONTROLS_H
#define PLAYERCONTROLS_H

#include <math.h>
#include "Controller.h"
#include "ngl/Vec3.h"
#include "ngl/Vec4.h"

#define PLAYERCONTROLS_HIGHSPEED 0.25
#define PLAYERCONTROLS_HIGHSPEED_X 0.2
#define PLAYERCONTROLS_EMERSION_HIGH 0.2
#define PLAYERCONTROLS_LATERAL_STREAM_FORCE 0.03
#define PLAYERCONTROLS_AMPLITUDE_BOUNCING 0.03
#define PLAYERCONTROLS_FRECUENCY_BOUNCING M_PI/60


class PlayerControls : public Controller
{
private:
    bool m_left;
    bool m_right;
    bool m_speedUp;
    bool m_floating;
    bool m_bouncing;
    bool m_emerging;
    bool m_immersing;
    bool m_jumping;
    int m_ticksFloating;
    int m_ticksBouncing;
    int m_ticksJumping;

public:
    PlayerControls();
    void setLeft(bool _pressed) { m_left = _pressed; }
    void setRight(bool _pressed) { m_right = _pressed; }
    void setSpeedUp(bool _pressed) { m_speedUp = _pressed; }
    virtual void move();
};

#endif // PLAYERCONTROLS_H

#ifndef PLAYERCONTROLS_H
#define PLAYERCONTROLS_H

#include <math.h>
#include "Controller.h"
#include "ngl/Vec3.h"
#include "ngl/Vec4.h"

#define CAMBER 1
#define FRECUENCY 1
#define AMPLITUDE 1

class PlayerControls : public Controller
{
private:
    bool m_left;
    bool m_right;
    bool m_speedUp;
    int m_ticks;

public:
    void setLeft(bool _pressed);
    void setRight(bool _pressed);
    void setSpeedUp(bool _pressed);
    void move(ngl::Vec3 &_pos, ngl::Vec4 &_rot, const ngl::Vec4 &_velocity);
};

#endif // PLAYERCONTROLS_H

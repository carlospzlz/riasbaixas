#ifndef FLOATING_H
#define FLOATING_H

#include <math.h>
#include "Controller.h"
#include "SpeedBoat.h"

#define AMPLITUDE 3
#define FRECUENCY M_PI/150

class Floating : public Controller
{

private:
    int m_ticks;
    int m_push;

public:
    Floating();
    void move(ngl::Vec3 _p, ngl::Vec3 _v);

};

#endif // FLOATING_H

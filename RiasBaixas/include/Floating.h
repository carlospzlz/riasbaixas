#ifndef FLOATING_H
#define FLOATING_H

#include <math.h>
#include "Controller.h"

#define AMPLITUDE 3
#define FRECUENCY M_PI/150

class Floating : public Controller
{

private:
    int m_ticks;
    //write it with the velocity vector

public:
    Floating();
    void move(ngl::Vec3 &_p, ngl::Vec3 &_v);

};

#endif // FLOATING_H

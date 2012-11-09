#ifndef FLOATING_H
#define FLOATING_H

#include <math.h>
#include "Controller.h"
#include "SpeedBoat.h"

#define AMPLITUDE 1
#define FRECUENCY M_PI/150

class Floating : public Controller
{

private:
    int m_ticks;

public:
    Floating();
    void handleMovement(DynamicSeaElement _dse);
    void handleCollision(DynamicSeaElement _dse, SpeedBoat _sp);

};

#endif // FLOATING_H

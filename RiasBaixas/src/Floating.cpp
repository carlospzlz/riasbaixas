#include "Floating.h"
#include <math.h>

Floating::Floating()
{
    //srand(time(NULL));
    //m_ticks = rand() % 10;
    m_ticks = 0;
}

void Floating::handleMovement(DynamicSeaElement _dse)
{
    _dse.setY(AMPLITUDE*sin(FRECUENCY*m_ticks));
    ++m_ticks;
}

void Floating::handleCollision(DynamicSeaElement _dse, SpeedBoat _sp)
{

}

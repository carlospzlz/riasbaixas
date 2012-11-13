#include "Floating.h"
#include <math.h>

Floating::Floating()
{
    //srand(time(NULL));
    //m_ticks = rand() % 10;
    m_ticks = 0;
}

void Floating::move(ngl::Vec3 &_p, ngl::Vec3 &_v)
{
    _p += _v;

    _v.m_y = AMPLITUDE*cos(FRECUENCY*m_ticks);
    if (_v.m_x > 0)
        --_v.m_x;
    if (_v.m_z > 0)
        --_v.m_z;
    ++m_ticks;
}

//void Floating::handleCollision(DynamicSeaElement _dse, SpeedBoat _sp)
//{

//}

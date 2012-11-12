#include "Floating.h"
#include <math.h>

Floating::Floating()
{
    //srand(time(NULL));
    //m_ticks = rand() % 10;
    m_ticks = 0;
    m_push = 0;
}

void Floating::move(ngl::Vec3 _p, ngl::Vec3 _v)
{
    _p.m_y = AMPLITUDE*sin(FRECUENCY*m_ticks);
    if (m_push)
    {
        _p += _v;
        --m_push;
    }
    ++m_ticks;
}

//void Floating::handleCollision(DynamicSeaElement _dse, SpeedBoat _sp)
//{

//}

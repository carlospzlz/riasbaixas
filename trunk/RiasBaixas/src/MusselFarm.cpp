#include <MusselFarm.h>

MusselFarm::MusselFarm(ngl::Obj *_model, ngl::Vec3 _pos) : StaticSeaElement(_model, "cube", _pos)
{
    m_damage = DAMAGE;
}

MusselFarm::MusselFarm(ngl::Vec3 _pos) : StaticSeaElement(NULL, "cube", _pos)
{
    m_damage = DAMAGE;
}

int inline MusselFarm::getDamage()
{
    return m_damage;
}

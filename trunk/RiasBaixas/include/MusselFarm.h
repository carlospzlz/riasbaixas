#ifndef MUSSELFARM_H
#define MUSSELFARM_H

#include <StaticSeaElement.h>

#define DAMAGE 10

class MusselFarm : public StaticSeaElement
{
private:
    int m_damage;

public:
    MusselFarm(ngl::Obj *_model, ngl::Vec3 _pos);
    MusselFarm(ngl::Vec3 _pos);
    int inline getDamage();

};

#endif // MUSSELFARM_H

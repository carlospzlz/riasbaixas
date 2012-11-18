#ifndef MUSSELFARM_H
#define MUSSELFARM_H

#include "StaticObject.h"

#define MUSSELFARM_DAMAGE 10

class MusselFarm : public StaticObject
{

public:
    MusselFarm(ngl::Obj *_model, ngl::Vec3 _pos);
    MusselFarm(ngl::Vec3 _pos);

};

#endif // MUSSELFARM_H

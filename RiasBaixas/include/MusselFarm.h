#ifndef MUSSELFARM_H
#define MUSSELFARM_H

#include "StaticObject.h"

#define DAMAGE 10

class MusselFarm : public StaticObject
{

public:
    MusselFarm(ngl::Obj *_model, ngl::Vec3 _pos, int _dam);
    MusselFarm(ngl::Vec3 _pos, int _dam);

};

#endif // MUSSELFARM_H

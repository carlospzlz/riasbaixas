#include <MusselFarm.h>

MusselFarm::MusselFarm(ngl::Obj *_model, ngl::Vec3 _pos) :
    StaticObject(ot_musselFarm, _model, "cube", _pos, ngl::Vec4(0,0,0,1), ngl::Vec4(1,1,1,1), MUSSELFARM_DAMAGE)
{
    std::cout << "MusselFarm created." << std::endl;
}

MusselFarm::MusselFarm(ngl::Vec3 _pos) :
    StaticObject(ot_musselFarm, NULL, "cube", _pos, ngl::Vec4(0,0,0,1), ngl::Vec4(1,1,1,1), MUSSELFARM_DAMAGE)
{
    std::cout << "MusselFarm created." << std::endl;
}

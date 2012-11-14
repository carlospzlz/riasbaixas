#include <MusselFarm.h>

MusselFarm::MusselFarm(ngl::Obj *_model, ngl::Vec3 _pos) :
    StaticSeaElement(set_musselFarm, _model, "cube", _pos, ngl::Vec4(0,0,0,1), ngl::Vec4(0,0,0,1))
{
    m_damage = DAMAGE;
    std::cout << "MusselFarm created." << std::endl;
}

MusselFarm::MusselFarm(ngl::Vec3 _pos) : StaticSeaElement(set_musselFarm, NULL, "cube", _pos, ngl::Vec4(0,0,0,1), ngl::Vec4(0,0,0,1) )
{
    m_damage = DAMAGE;
    std::cout << "MusselFarm created." << std::endl;
}

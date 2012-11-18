#ifndef OBJECT_H
#define OBJECT_H

#include <ngl/Obj.h>
#include <ngl/Vec3.h>
#include <ngl/Vec4.h>
#include <ngl/Transformation.h>
#include <ngl/Camera.h>
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>

enum  objectType
{
    ot_musselFarm,
    ot_ramp,
    ot_stream,
    ot_rock,
    ot_speedBoat,
    ot_policeBoat,
    ot_fisheBoat,
    ot_dolphin,
    ot_Seagull
};


class Object
{

protected:
    objectType m_type;
    ngl::Obj *m_mesh;
    std::string m_primName;
    ngl::Vec3 m_position;
    ngl::Vec4 m_rotation;
    ngl::Vec4 m_scale;
    int m_damage;
    ngl::Transformation m_transform;
    Object(objectType _type, ngl::Obj *_model, std::string _primName, ngl::Vec3 _pos, ngl::Vec4 _rot, ngl::Vec4 _sca, int _dam);

public:
    void draw(const std::string &_shader, const ngl::Camera &_cam, int _debugMode);
    objectType getObjectType() {return m_type;}
    float getY() { return m_position.m_y; }
    float getZ() { return m_position.m_z; }
    void info();
    //virtual void interactWith(Object _o);

};

#endif // OBJECT_H

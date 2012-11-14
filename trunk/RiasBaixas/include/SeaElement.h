#ifndef SEAELEMENT_H
#define SEAELEMENT_H

#include <ngl/Obj.h>
#include <ngl/Vec3.h>
#include <ngl/Vec4.h>
#include <ngl/Transformation.h>
#include <ngl/Camera.h>
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>

enum  SeaElementType
{
    set_musselFarm,
    set_ramp,
    set_stream,
    set_rock,
    set_speedBoat,
    set_policeBoat,
    set_fisheBoat,
    set_dolphin,
    set_Seagull
};


class SeaElement
{

protected:
    SeaElementType m_type;
    ngl::Obj *m_model;
    std::string m_primName;
    ngl::Vec3 m_position;
    ngl::Vec4 m_rotation;
    ngl::Vec4 m_scale;
    ngl::Transformation m_transform;
    SeaElement(SeaElementType _type, ngl::Obj *_model, std::string _primName, ngl::Vec3 _pos, ngl::Vec4 _rot, ngl::Vec4 _sca);

public:
    void draw(const std::string &_shader, const ngl::Camera &_cam, int _debugMode);
    SeaElementType getSeaElementType() {return m_type;}

};

#endif // SEAELEMENT_H

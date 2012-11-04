#ifndef SPEEDBOAT_H
#define SPEEDBOAT_H

#include <ngl/Obj.h>
#include <ngl/Transformation.h>
#include <ngl/Vec3.h>
#include <ngl/ShaderLib.h>

#define MAX_LOAD 300;

class SpeedBoat
{
private:
    ngl::Obj *m_model;
    ngl::Vec3 m_position;
    ngl::Vec3 m_rotation;
    ngl::Transformation m_transform;
    int m_load;

public:
    SpeedBoat() { };
    SpeedBoat(ngl::Obj *_model);
    void draw();
};

#endif // SPEEDBOAT_H

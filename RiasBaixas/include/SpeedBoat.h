#ifndef SPEEDBOAT_H
#define SPEEDBOAT_H

#include <ngl/Obj.h>
#include <ngl/Transformation.h>
#include <ngl/Vec3.h>
#include <ngl/ShaderLib.h>
#include <ngl/Camera.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/TransformStack.h>
#include <ngl/Material.h>
#include <ngl/Light.h>

#define MAX_LOAD 300;

class SpeedBoat
{
private:
    ngl::Obj *m_model;
    ngl::Vec3 m_position;
    ngl::Vec4 m_rotation;
    ngl::Transformation m_transform;
    int m_load;
    int ticks;

public:
    SpeedBoat() { };
    SpeedBoat(ngl::Obj *_model);
    void draw(const std::string &_shader, ngl::Camera *_cam);
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    void rotateInY();
    void rotateInX();
    void rotateInZ();
    void floating();
};

#endif // SPEEDBOAT_H

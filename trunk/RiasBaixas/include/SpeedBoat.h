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

#include "DynamicSeaElement.h"


#define MAX_LOAD 300;

class SpeedBoat : public DynamicSeaElement
{
private:
    ngl::Vec3 m_position;
    ngl::Vec4 m_rotation;
    ngl::Vec4 m_scale;
    ngl::Transformation m_transform;
    int m_load;
    int ticks;

public:
    SpeedBoat(Controller *_controller, ngl::Obj *_model);
    void draw(const std::string &_shader, ngl::Camera *_cam, int _debugMode);
    void move();
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

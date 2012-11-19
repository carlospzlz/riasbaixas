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

#include "DynamicObject.h"

#define SPEEDBOAT_SPEED 0.01
#define SPEEDBOAT_SPEED_FACTOR 3
#define SPEEDBOAT_COMBER_STEP 2
#define SPEEDBOAT_COMBER_MAX 20
#define MAX_LOAD 300;

class SpeedBoat : public DynamicObject
{
private:
    int m_load;
    int ticks;

public:
    SpeedBoat(Controller *_controller, ngl::Obj *_mesh, int _dam);
    SpeedBoat(Controller *_controller, int _dam);
    virtual void move();
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

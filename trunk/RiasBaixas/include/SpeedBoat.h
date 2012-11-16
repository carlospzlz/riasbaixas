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
    int m_load;
    int ticks;

public:
    SpeedBoat(Controller *_controller, ngl::Obj *_model);
    SpeedBoat(Controller *_controller);
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

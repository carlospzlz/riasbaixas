#ifndef DYNAMICSEAELEMENT_H
#define DYNAMICSEAELEMENT_H

#include <ngl/Vec3.h>
#include "Controller.h"

class DynamicSeaElement
{

private:
    ngl::Vec3 m_position;
    int m_speed;
    Controller *m_controller;

public:
    DynamicSeaElement(Controller *_c, int _speed);
    float getX() { return m_position.m_x; }
    float getY() { return m_position.m_y; }
    float getZ() { return m_position.m_z; }
    void setX(float _x) {m_position.m_x = _x; }
    void setY(float _y) {m_position.m_y = _y; }
    void setZ(float _z) {m_position.m_z = _z; }

    void draw(bool _debuggingMode);
    void move();

};

#endif // DYNAMICSEAELEMENT_H

#ifndef SEA_H
#define SEA_H

#include <ngl/Obj.h>
#include <ngl/Camera.h>
#include <ngl/ShaderLib.h>

#define SEA_WIDTH 20
#define SEA_DEPTH 3000

class Sea
{
    //private *ngl::Obj model
public:
    Sea();
    void draw(const std::string &_shader, ngl::Camera &_cam);
};

#endif // SEA_H

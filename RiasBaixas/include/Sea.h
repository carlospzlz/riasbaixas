#ifndef SEA_H
#define SEA_H

#include <ngl/Obj.h>
#include <ngl/Camera.h>
#include <ngl/ShaderLib.h>

class Sea
{
    //private *ngl::Obj model
public:
    Sea();
    void draw(const std::string &_shader, ngl::Camera &_cam);
};

#endif // SEA_H

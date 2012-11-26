#ifndef SEA_H
#define SEA_H

#include <ngl/Obj.h>
#include <ngl/Camera.h>
#include <ngl/ShaderLib.h>

#define SEA_WIDTH 16
#define SEA_DEPTH 3000
#define SEA_FLOATING_HIGH 0.3

class Sea
{
    //private *ngl::Obj model
private:
    float m_depth;
    std::string m_primName;

public:
    Sea();
    void setDepth(float _depth) { m_depth = _depth; }
    void draw(const std::string &_shader, ngl::Camera &_cam);

    ngl::Obj *getMesh() const { return NULL; }
    std::string getPrimName() const { return m_primName; }
};

#endif // SEA_H

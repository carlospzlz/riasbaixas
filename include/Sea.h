#ifndef SEA_H
#define SEA_H

/**
 * @file Sea.h
 * @brief This the background of the 3D world
 */
#include <ngl/Obj.h>
#include <ngl/Camera.h>
#include <ngl/ShaderLib.h>

#define SEA_WIDTH 12
#define SEA_DEPTH 3000
#define SEA_FLOATING_HIGH 0.3

/**
 * @class Sea
 * @brief This is the background of the 3D world
 */
class Sea
{

private:
    /**
     * @brief size of the see in the Z axis
     */
    float m_depth;
    /**
     * @brief name of the primitive used in debugmode or if there is no mesh
     */
    std::string m_primName;
    /**
     * @brief ngl::Obj to store the mesh of the sea
     */
    ngl::Obj* m_mesh;

public:
    Sea();
    void setDepth(float _depth);
    void setMesh(ngl::Obj* _mesh) { m_mesh = _mesh; }

    bool hasMesh() const { return m_mesh; }
    ngl::Obj* getMesh() const { return m_mesh; }
    std::string getPrimName() const { return m_primName; }
};

#endif // SEA_H

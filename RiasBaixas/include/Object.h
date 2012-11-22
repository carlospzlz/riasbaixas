#ifndef OBJECT_H
#define OBJECT_H

#include <ngl/Obj.h>
#include <ngl/Vec3.h>
#include <ngl/Vec4.h>
#include <ngl/Transformation.h>
#include <ngl/Camera.h>
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>

#include "Sea.h"
#include "Controller.h"

enum  objectType
{
    ot_object,
    ot_musselFarm,
    ot_ramp,
    ot_stream,
    ot_rock,
    ot_speedBoat,
    ot_policeBoat,
    ot_fisheBoat,
    ot_dolphin,
    ot_seagull
};


class Object
{

protected:
    bool m_active;
    ngl::Vec3 m_position;
    ngl::Vec3 m_previousPos;
    ngl::Vec4 m_rotation;
    ngl::Vec4 m_scale;
    ngl::Vec3 m_velocity;
    float m_maxSpeed;
    float m_mass;
    degreesOfFreedom m_degreesOfFreedom;
    objectType m_type;
    ngl::Obj *m_mesh;
    std::string m_primName;
    int m_damage;
    bool m_jumping;
    ngl::Transformation m_transform;
    Controller *m_controller;

    void updateActive(float _currentZ);

public:
    Object();
    ~Object() { }
    //setters
    void activate() { m_active = true; }
    void setPosition(ngl::Vec3 _pos);
    //void setPreviousPos(ngl::Vec3 _prevPos) { m_previousPos = _prevPos; }
    void setRotation(ngl::Vec3 _rot) { m_rotation = _rot; }
    void setScale(ngl::Vec3 _sca) { m_position = _sca; }
    void setVelocity(ngl::Vec3 _vel) { m_velocity = _vel; }
    void setMaxSpeed(float _mSpe) { m_maxSpeed = _mSpe; }
    void setMass(float _mass) { m_mass = _mass; }
    void setType(objectType _ot) { m_type = _ot; }
    void setMesh(ngl::Obj *_mesh) { m_mesh = _mesh; }
    void setPrimName(std::string _prim) { m_primName = _prim; }
    void setDamage(int _dam) { m_damage = _dam; }
    void setJumping(bool _jump) { m_jumping = _jump; }
    void setController(Controller *_cont) { m_controller = _cont; }

    //getters
    bool isActive() { return m_active; }
    ngl::Vec3 getPosition() { return m_position; }
    ngl::Vec3 getPreviousPos() { return m_previousPos; }
    objectType getObjectType() { return m_type; }
    degreesOfFreedom &getDOF() { return m_degreesOfFreedom; } //will change it, I think so...

    //methods
    void draw(const std::string &_shader, const ngl::Camera &_cam, int _debugMode);
    void info();
    virtual void update(float _currentZ, float _far);
    virtual void collisionEvent(Object _o);

};

#endif // OBJECT_H

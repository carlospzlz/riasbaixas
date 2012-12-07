#ifndef OBJECT_H
#define OBJECT_H

#include <ngl/Obj.h>
#include <ngl/Vec3.h>
#include <ngl/Vec4.h>
#include <ngl/Transformation.h>
#include <ngl/TransformStack.h>
#include <ngl/Camera.h>
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>


enum  objectType
{
    ot_object,
    ot_musselFarm,
    ot_ramp,
    ot_stream,
    ot_rock,
    ot_speedBoat,
    ot_policeBoat,
    ot_fisherBoat,
    ot_dolphin,
    ot_seagull
};


struct degreesOfFreedom
{
    bool forward;
    bool backward;
    bool left;
    bool right;
    bool up;
    bool down;
};


class Object
{

protected:
    bool m_active;
    ngl::Transformation m_transform;
    ngl::Transformation m_previousTransform;
    float m_mass;
    ngl::Vec4 m_velocity;
    ngl::Vec4 m_angularVelocity;
    float m_maxSpeed;
    float m_maxCamber;
    degreesOfFreedom m_degreesOfFreedom;
    objectType m_type;
    ngl::Obj *m_mesh;
    std::string m_primName;
    float m_bSRadius;
    int m_damage;
    bool m_jumping;
    bool m_collided;

    void updateActive(float _currentZ);

public:
    Object();
    //not needed copy constructor
    //setters
    void activate() { m_active = true; }
    void setPosition(ngl::Vec4 _pos);
    //void setPreviousPos(ngl::Vec3 _prevPos) { m_previousPos = _prevPos; }
    void setRotation(ngl::Vec4 _rot) { m_transform.setRotation(_rot); }
    void setScale(ngl::Vec4 _sca) { m_transform.setScale(_sca); }
    void setPreviousPos(ngl::Vec4 _pos) { m_previousTransform.setPosition(_pos); }
    void setPreviousRot(ngl::Vec4 _rot) { m_previousTransform.setRotation(_rot); }
    void setVelocity(ngl::Vec4 _vel) { m_velocity = _vel; }
    void setAngularVelocity(ngl::Vec4 _aVel) { m_angularVelocity = _aVel; }
    void setMaxSpeed(float _mSpe) { m_maxSpeed = _mSpe; }
    void setMass(float _mass) { m_mass = _mass; }
    void setType(objectType _ot) { m_type = _ot; }
    void setMesh(ngl::Obj *_mesh);
    void setPrimName(std::string _prim) { m_primName = _prim; }
    void setDamage(int _dam) { m_damage = _dam; }
    void setJumping(bool _jump) { m_jumping = _jump; }
    void setCollided(bool _collided) {m_collided = _collided; }

    //getters
    bool isActive() const { return m_active; }
    ngl::Transformation getTransform() { return m_transform; }
    ngl::Vec4 getPosition() const { return m_transform.getPosition(); }
    ngl::Vec4 getPreviousPos() const { return m_previousTransform.getPosition(); }
    ngl::Vec4 getRotation() const { return m_transform.getRotation(); }
    ngl::Vec4 getScale() const { return m_transform.getScale(); }
    float getMass() const { return m_mass; }
    std::string getType();
    degreesOfFreedom &getDOF() { return m_degreesOfFreedom; } //will change it, I think so...
    ngl::Obj *getMesh() const { return m_mesh; }
    std::string getPrimName() const { return m_primName; }
    ngl::Vec4 getVelocity() const { return m_velocity; }
    ngl::Vec4 getAngularVelocity() const { return m_angularVelocity; }
    bool isJumping() const { return m_jumping; }
    float getMaxSpeed() const { return m_maxSpeed; }
    float getMaxCamber() const { return m_maxCamber; }
    bool hasMesh() const { return m_mesh; }
    float getBSRadius() const { return m_bSRadius; }
    bool isCollided() const { return m_collided; }

    //methods
    void draw(const std::string &_shader, const ngl::Camera &_cam, int _debugMode);
    void info();
    void checkActive(float _currentZ, float _far);
    virtual void collisionEvent(Object &_o);

};

#endif // OBJECT_H

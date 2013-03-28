#ifndef OBJECT_H
#define OBJECT_H

/**
 * @file Object.h
 * @brief A simple object of a 3D scene
 */
#include <ngl/Obj.h>
#include <ngl/Vec3.h>
#include <ngl/Vec4.h>
#include <ngl/Transformation.h>
#include <ngl/TransformStack.h>
#include <ngl/Camera.h>
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>

#include "Behaviour.h"

/**
 * @enum objectType
 * @brief the specific type of an object in the context of the sea
 */
enum objectType
{
    ot_object,
    ot_musselFarm,
    ot_rock,
    ot_speedBoat,
    ot_policeBoat,
    ot_fisherBoat
};

/**
 * @class Object
 * @brief This class represents a simple object in a 3D scene
 * @author Carlos Pérez López
 */
class Object
{

protected:
    /**
     * @brief flag to determine if the object is active (visible) or not
     */
    bool m_active;
    /**
     * @brief current transformation of the object
     */
    ngl::Transformation m_transform;
    /**
     * @brief previous transformation of the object
     */
    ngl::Transformation m_previousTransform;
    /**
     * @brief mass of the object, used to calculate acceleration (a = F/m).
     * Mass 0 means the object is completely static
     */
    float m_mass;
    /**
     * @brief linear velocity of the object
     */
    ngl::Vec4 m_velocity;
    /**
     * @brief angular velocity of the object
     */
    ngl::Vec4 m_angularVelocity;
    /**
     * @brief maximum speed that the obejct can reach
     */
    float m_maxSpeed;
    /**
     * @brief to which directions the object can move
     */
    degreesOfFreedom m_degreesOfFreedom;
    /**
     * @brief internal type of the object in the context of the sea
     */
    objectType m_type;
    /**
     * @brief ngl::obj which stores the mesh and texture of the object
     */
    ngl::Obj *m_mesh;
    /**
     * @brief name of the primitive used for debugging of if there is no mesh assinged
     */
    std::string m_primName;
    /**
     * @brief radious of the bounding sphere
     */
    float m_bSRadius;
    /**
     * @brief damage that the object provoques in a collision
     */
    int m_damage;
    /**
     * @brief state of jumping (used by AI)
     */
    bool m_collided;
    /**
     * @brief specific behaviour of the object, it determines how the object moves
     */
    Behaviour *m_behaviour;

public:
    /**
     * @brief constructor of the object which sets all the attibutes to default values
     */
    Object();
    virtual ~Object();
    //not needed copy constructor
    //setters
    void activate() { m_active = true; }
    void setBehaviour(Behaviour *b);
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
    void setCollided(bool _collided) {m_collided = _collided; }

    //getters
    bool isActive() const { return m_active; }
    virtual void update();
    ngl::Transformation getTransform() { return m_transform; }
    ngl::Vec4 getPosition() const { return m_transform.getPosition(); }
    ngl::Vec4 getPreviousPos() const { return m_previousTransform.getPosition(); }
    ngl::Vec4 getRotation() const { return m_transform.getRotation(); }
    ngl::Vec4 getScale() const { return m_transform.getScale(); }
    float getMass() const { return m_mass; }
    std::string getType();
    degreesOfFreedom &getDOF() { return m_degreesOfFreedom; }
    ngl::Obj *getMesh() const { return m_mesh; }
    std::string getPrimName() const { return m_primName; }
    ngl::Vec4 getVelocity() const { return m_velocity; }
    ngl::Vec4 getAngularVelocity() const { return m_angularVelocity; }
    float getMaxSpeed() const { return m_maxSpeed; }
    bool hasMesh() const { return m_mesh; }
    float getBSRadius() const { return m_bSRadius; }
    bool isCollided() const { return m_collided; }

    //methods
    /**
     * @brief print info of the object to the standard output
     */
    void info();
    /**
     * @brief check if an object is active (visible) or not,depending
     * on the current Z where the player is a the far clipping plane of the cameras
     */
    void checkActive(float _currentZ, float _far);
    /**
     * @brief event launched when a collision with an object takes place, the specific
     * behaviour of this method should be implemented by the children classes
     */
    virtual void collisionEvent(Object &_o);

};

#endif // OBJECT_H

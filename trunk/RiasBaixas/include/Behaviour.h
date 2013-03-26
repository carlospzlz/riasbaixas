#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

/**
 * @file Behaviour.h
 * @brief This is the abstract class of any specific behaviour/control of an Object.
 * Module of artificial intelligence
 */

#include <time.h>
#include <math.h>
#include <ngl/Vec3.h>
#include <ngl/Transformation.h>
#include "Sea.h"


/**
 * @struct degreesOfFreedom
 * @brief specifies the directions an object can move towards in the 3D space,
 * this information is used by the AI module.
 */
struct degreesOfFreedom
{
    bool forward;
    bool backward;
    bool left;
    bool right;
    bool up;
    bool down;
};

/**
 * @class Behaviour.cpp
 * @brief This is the abstract class of any specific behaviour/control of an Object.
 * Module of artificial intelligence
 */
class Behaviour
{

private:

    float m_floatingAmplitude;
    float m_floatingFrequency;


    /**
     * @brief ticks for the floating behaviour in Y
     */
    int m_ticksFloating;
    /**
     * @brief friction force which makes the object break
     */
    //float m_frictionForce;
    /**
     * @brief speed (added in each iteration to the velocity)
     */
    //float m_speed;
    /**
     * @brief amplitude of the floating movement
     */
    //float m_floatingAmplitude;
    /**
     * @brief frecuency of the floating movement
     */
    //float m_floatingFrecuency;
    /**
     * @brief velocity of the rotation
     */
    //float m_angularVelocity;

protected:

    float m_frictionForce;
    float m_regularSpeed;
    float m_motorForce;
    float m_angularVelocity;
    float m_maxCamber;

    /**
     * @brief acceleration calculate from a = F*m when the controlled object is set
     */
    ngl::Vec4 m_acceleration;
    /**
     * @brief calculate the floating velocity in Y
     */
    float floatingVelocity();
    /**
     * @brief reset the calculation of the floating movement setting floating ticks to 0 again
     */
    void resetFloatingVelocity() { m_ticksFloating=0; }

public:
    Behaviour();
    virtual std::string getName() = 0;
    /**
     * @brief method which sets the acceleration according with the object this behaviour belongs to
     */
    void setAcceleration(float _mass);

    void setFloatingAmplitude(float _fa) { m_floatingAmplitude = _fa; }
    void setFloatingFrequency(float _ff) { m_floatingFrequency = _ff; }
    void setFrictionForce(float _ff) { m_frictionForce = _ff; }
    void setRegularSpeed(float _rs) { m_regularSpeed = _rs; }
    void setMotorForce(float _mf) { m_motorForce = _mf; }
    void setAngularVelocity(float _av) {m_angularVelocity = _av; }
    void setMaxCamber(float _mc) { m_maxCamber = _mc; }

    /**
     * @brief method which moves the object and where the AI takes place
     */
    virtual void move(ngl::Transformation &_transform, ngl::Vec4 &_velocity, ngl::Vec4 &_angularVelocity, degreesOfFreedom &_dof) = 0;

};

#endif // BEHAVIOUR_H

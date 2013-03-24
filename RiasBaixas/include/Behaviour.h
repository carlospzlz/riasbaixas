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

#define CONTROLLER_FRICTION_FORCE 0.001
#define CONTROLLER_SPEED 0.1
#define CONTROLLER_MOTOR_FORCE 0.005
#define CONTROLLER_FLOATING_AMPLITUDE 0.008
#define CONTROLLER_FLOATING_FRECUENCY M_PI/40
#define CONTROLLER_ANGULAR_VELOCITY 2
#define CONTROLLER_CAMBER 30

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

    const static float s_floatingAmplitude;
    const static float s_floatingFrequency;


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

    const static float s_frictionForce;
    const static float s_regularSpeed;
    const static float s_motorForce;
    const static float s_angularVelocity;
    const static float s_camber;

    /**
     * @brief acceleration calculate from a = F*m when the controlled object is set
     */
    ngl::Vec4 m_acceleration;
    /**
     * @brief acceleration calculate from a = F*m when the controlled object is set
     */
    ngl::Vec4 m_camber;
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
    /**
     * @brief method which moves the object and where the AI takes place
     */
    virtual void move(ngl::Transformation &_transform, ngl::Vec4 &_velocity, ngl::Vec4 &_angularVelocity, degreesOfFreedom &_dof) = 0;

};

#endif // BEHAVIOUR_H

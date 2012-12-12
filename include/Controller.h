#ifndef CONTROLLER_H
#define CONTROLLER_H

/**
 * @file Controller.h
 * @brief This is the abstract class of any specific behaviour/control of an Object.
 * Module of artificial intelligence
 */

#include <time.h>
#include <math.h>
#include <ngl/Vec3.h>
#include <ngl/Transformation.h>
#include "Object.h"
#include "Sea.h"

#define CONTROLLER_FRICTION_FORCE 0.001
#define CONTROLLER_SPEED 0.1
#define CONTROLLER_MOTOR_FORCE 0.005
#define CONTROLLER_FLOATING_AMPLITUDE 0.008
#define CONTROLLER_FLOATING_FRECUENCY M_PI/40
#define CONTROLLER_ANGULAR_VELOCITY 2
#define CONTROLLER_CAMBER 30

/**
 * @class Controller
 * @brief This is the abstract class of any specific behaviour/control of an Object.
 * Module of artificial intelligence
 */
class Controller
{

private:
    /**
     * @brief ticks for the floating behaviour in Y
     */
    int m_ticksFloating;

protected:
    /**
     * @brief Object controlled by this controller
     */
    Object* m_object;
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
    Controller();
    void setControlledObject(Object* _o);
    /**
     * @brief a controller is active if it has an object assigned and this object is active
     */
    bool isActive() { return m_object!=NULL && m_object->isActive(); }
    /**
     * @brief method which moves the object and where the AI takes place
     */
    virtual void move();

};

#endif // CONTROLLER_H

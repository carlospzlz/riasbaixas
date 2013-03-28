#ifndef PREDATOR_H
#define PREDATOR_H

/**
 * @file Predator.h
 * @brief Behaviour that steers an object to chase another object which is the prey
 */

#include "Behaviour.h"
#include "PlayerControls.h"
#include "Object.h"
#include "TXTParser.h"

/**
 * @class Predator
 * @brief Behaviour that steers an object to chase another object which is the prey
 */

class Predator : public Behaviour
{

private:
    /**
     * @brief object that is the target to chase
     */
    Object *m_prey;
    /**
     * @brief player controls used as controller interface
     */
    PlayerControls *m_controls;

public:
    Predator();
    /**
     * @brief set the pray
     */
    void setPrey(Object* _p) { m_prey = _p; }
    virtual std::string getName() { return "Predator"; }
    virtual void move(ngl::Transformation &_transform, ngl::Vec4 &_velocity, ngl::Vec4 &_angularVelocity, degreesOfFreedom &_dof);
};

#endif // PREDATOR_H

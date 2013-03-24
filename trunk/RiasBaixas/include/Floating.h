#ifndef FLOATING_H
#define FLOATING_H

/**
 * @file Floating.h
 * @brief Most basic movement where the force of friction is implemented to recover the initial position
 */
#include <math.h>
#include "Behaviour.h"

/**
 * @class Floating
 * @brief Most basic movement where the force of friction is implemented to recover the initial position
 */
class Floating : public Behaviour
{

public:
    virtual std::string getName() { return "Floating"; }
    virtual void move(ngl::Transformation &_transform, ngl::Vec4 &_velocity, ngl::Vec4 &_angularVelocity, degreesOfFreedom &_dof);

};

#endif // FLOATING_H

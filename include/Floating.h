#ifndef FLOATING_H
#define FLOATING_H

/**
 * @file Floating.h
 * @brief Most basic movement where the force of friction is implemented to recover the initial position
 */
#include <math.h>
#include "Controller.h"

/**
 * @class Floating
 * @brief Most basic movement where the force of friction is implemented to recover the initial position
 */
class Floating : public Controller
{

public:
    virtual void move();

};

#endif // FLOATING_H

#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

/**
 * @file PhysicsEngine
 * @brief General abstract class of a physics engine, responsible of calculate
 * and handle the collisions among the objects in the world
 */
#include "Object.h"

/**
 * @class PhysicsEngine
 * @brief General abstract class of a physics engine, responsible of calculate
 * the collisions among the objects in the world
 */
class PhysicsEngine
{

protected:
    /**
     * @brief returns true if there is a collision between two objects
     */
    virtual bool thereIsCollision(Object &_o1, Object &_o2) { }

public:
    /**
     * @brief checks the collision between two objects; fixing the position,
     * updating the degrees of freedom and calling the collision event for each object
     */
    virtual void checkCollision(Object *_o1, Object *_o2) { }

};

#endif // PHYSICSENGINE_H

#ifndef BSPHEREPE_H
#define BSPHEREPE_H

/**
 * @file BSpherePE.h
 * @brief specific PhysicsEngine based on the bounding sphere
 */
#include "PhysicsEngine.h"

/**
 * These data structs are used to calculate information about the collision.
 * The collisions of the objects are calculated with a bounceing sphere, but
 * six different type of collision can be distinguished, according with the
 * relationship between the o1 and o2 at the time of the impact.
 */

/**
 * @struct collisionData
 * @brief this struct describes the 6 possible directions of a collision from the
 * point of view of the first object
 */
struct collisionData
{
    bool up;
    bool down;
    bool left;
    bool right;
    bool forward;
    bool backward;
};

/**
 * @struct collisionProjection
 * @brief this struct represents the projection of the vector which goes from
 * the centre of the object 1 to the centre of the object 2. Using the three
 * projections of a collision is possible to calculate its direction.
 */
struct collisionProjection
{
    bool up;
    bool down;
    bool left;
    bool right;
};

/**
 * @class BSpherePE
 * @brief specific physicsEngine based on the bounding sphere
 */
class BSpherePE : public PhysicsEngine
{

private:
    /**
    * @brief calculate the projection of a collision vector in 2D
    */
    void calculateCollisionProjection(collisionProjection &_projection, float _x1, float _y1, float _x2, float _y2);

protected:
    bool thereIsCollision(const Object &_o1, const Object &_o2);

public:
    void checkCollision(Object *_o1, Object *_o2);

};

#endif // BSPHEREPE_H

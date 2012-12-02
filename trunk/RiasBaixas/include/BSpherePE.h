#ifndef BSPHEREPE_H
#define BSPHEREPE_H

#include "PhysicsEngine.h"

/**
 * These data structs are used to calculate information about the collision.
 * The collisions of the objects are calculated with a bounceing sphere, but
 * six different type of collision can be distinguished, according with the
 * relationship between the o1 and o2 at the time of the impact.
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

struct collisionProjection
{
    bool up;
    bool down;
    bool left;
    bool right;
};

class BSpherePE : public PhysicsEngine
{

private:
    void calculateCollisionProjection(collisionProjection &_projection, float _x1, float _y1, float _x2, float _y2);

protected:
    bool thereIsCollision(const Object &_o1, const Object &_o2);

public:
    void checkCollision(Object *_o1, Object *_o2);

};

#endif // BSPHEREPE_H

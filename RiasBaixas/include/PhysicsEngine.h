#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include "Object.h"

class PhysicsEngine
{

protected:
    virtual bool thereIsCollision(Object &_o1, Object &_o2) { }

public:
    virtual void checkCollision(Object *_o1, Object *_o2) { }

};

#endif // PHYSICSENGINE_H

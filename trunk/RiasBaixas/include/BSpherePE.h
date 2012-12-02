#ifndef BSPHEREPE_H
#define BSPHEREPE_H

#include "PhysicsEngine.h"

class BSpherePE : public PhysicsEngine
{

private:
    float calculateSlope(float _x1, float _y1, float _x2, float _y2);

protected:
    bool thereIsCollision(const Object &_o1, const Object &_o2);

public:
    void checkCollision(Object *_o1, Object *_o2);

};

#endif // BSPHEREPE_H

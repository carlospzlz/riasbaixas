#include "BSpherePE.h"

void BSpherePE::checkCollision(Object *_o1, Object *_o2)
{
    //std::cout << "Cheking " << _o1->getType() << " with " << _o2->getType() << " and...";

    if (thereIsCollision(*_o1,*_o2))
    {
        //std::cout << " COLLISION" << std::endl;
        _o1->collisionEvent(*_o2);
        _o2->collisionEvent(*_o1);
    }
    // else do nothing, it might have collided with other objects
    //std::cout << " NOTHING" << std::endl;
}

bool BSpherePE::thereIsCollision(Object const &_o1, const Object &_o2)
{
    float distance = std::sqrt(std::pow(_o1.getPosition().m_x-_o2.getPosition().m_x, 2) +
                               std::pow(_o1.getPosition().m_y-_o2.getPosition().m_y, 2) +
                               std::pow(_o1.getPosition().m_z-_o2.getPosition().m_z, 2) );
    return distance < (_o1.getBSRadius()+_o2.getBSRadius());
}

float BSpherePE::calculateSlope(float _x1, float _y1, float _x2, float _y2)
{

}

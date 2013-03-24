#ifndef POLICEBOAT_H
#define POLICEBOAT_H

#endif // POLICEBOAT_H

/**
 * @file PoliceBoat.h
 * @brief object controlled that will chase the player
 */
#include "Object.h"

/**
 * @class PoliceBoat
 * @brief object controlled by the player which represents a speed boat
 */
class PoliceBoat : public Object
{
private:
    /**
     * @brief the load of the boat. If it reaches 0, the player looses the game
     */
    std::Map<>;

public:
    PoliceBoat();
    ~PoliceBoat() { };

    /**
     * @brief specific collisionEvent implementation which will reduce the load
     * according with the damage produced by the object collided
     */
    void collisionEvent(Object &_o);
};

#endif // SPEEDBOAT_H


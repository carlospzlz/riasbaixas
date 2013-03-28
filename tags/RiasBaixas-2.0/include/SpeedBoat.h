#ifndef SPEEDBOAT_H
#define SPEEDBOAT_H

/**
 * @file SpeedBoat.h
 * @brief object controlled by the player which represents a speed boat
 */
#include "Object.h"

#define SPEEDBOAT_SPEED_FACTOR 3
#define SPEEDBOAT_COMBER_STEP 2
#define SPEEDBOAT_COMBER_MAX 20
#define SPEEDBOAT_MAX_LOAD 300;

/**
 * @class SpeedBoat
 * @brief object controlled by the player which represents a speed boat
 */
class SpeedBoat : public Object
{
private:
    /**
     * @brief the load of the boat. If it reaches 0, the player looses the game
     */
    int m_load;

public:
    SpeedBoat();
    void setLoad(int _l) { m_load = _l; }
    int getLoad() { return m_load; }

    /**
     * @brief specific collisionEvent implementation which will reduce the load
     * according with the damage produced by the object collided
     */
    void collisionEvent(Object &_o);
};

#endif // SPEEDBOAT_H

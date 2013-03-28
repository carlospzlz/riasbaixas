#ifndef POLICEBOAT_H
#define POLICEBOAT_H

/**
 * @file PoliceBoat.h
 * @brief object controlled that will chase the player
 */
#include "Object.h"
#include "Predator.h"

/**
 * @class PoliceBoat
 * @brief object controlled by the player which represents a police boat
 */
class PoliceBoat : public Object
{
private:
    /**
     * @brief the pray
     */
    Object *m_speedboat;
    bool m_chasing;

public:
    PoliceBoat();

    void setSpeedBoat( Object *_sb) { m_speedboat = _sb; }
    virtual void update();
    /**
     * @brief this collision event will check when it collides with the speedboat
     */
    void collisionEvent(Object &_o);
};

#endif // POLICEBOAT_H


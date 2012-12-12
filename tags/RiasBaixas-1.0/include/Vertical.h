#ifndef VERTICAL_H
#define VERTICAL_H

/**
 * @file Vertical.h
 * @brief movement parallel to the player advance
 */
#include "Controller.h"


/**
 * @class Vertical
 * @brief movement parallel to the player advance
 */
class Vertical : public Controller
{

private:
    /**
     * @brief boolean to store the direction of the movement
     */
    bool m_goingForward;

public:
    Vertical();
    virtual void move();

};

#endif // VERTICAL_H

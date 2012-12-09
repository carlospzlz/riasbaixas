#ifndef HORIZONTAL_H
#define HORIZONTAL_H

/**
 * @file Horizontal.h
 * @brief movement of a crossing boat from side to side on the sea
 */
#include "Controller.h"

/**
 * @class Horizontal
 * @brief represents the movement of a crossing boat on the sea
 */
class Horizontal : public Controller
{

private:
    /**
     * @brief boolean to store the direction of the horizontal movement
     */
    bool m_goingRight;

public:
    Horizontal();
    virtual void move();

};

#endif // HORIZONTAL_H

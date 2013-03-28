#ifndef HORIZONTAL_H
#define HORIZONTAL_H

/**
 * @file Horizontal.h
 * @brief movement of a crossing boat from side to side on the sea
 */
#include "Behaviour.h"

/**
 * @class Horizontal
 * @brief represents the movement of a crossing boat on the sea
 */
class Horizontal : public Behaviour
{

private:
    /**
     * @brief boolean to store the direction of the horizontal movement
     */
    bool m_goingRight;

public:
    Horizontal();
    virtual std::string getName() { return "Horizontal"; }
    virtual void move(ngl::Transformation &_transform, ngl::Vec4 &_velocity, ngl::Vec4 &_angularVelocity, degreesOfFreedom &_dof);

};

#endif // HORIZONTAL_H

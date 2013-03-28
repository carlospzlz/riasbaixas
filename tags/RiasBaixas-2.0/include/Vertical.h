#ifndef VERTICAL_H
#define VERTICAL_H

/**
 * @file Vertical.h
 * @brief movement parallel to the player advance
 */
#include "Behaviour.h"


/**
 * @class Vertical
 * @brief movement parallel to the player advance
 */
class Vertical : public Behaviour
{

private:
    /**
     * @brief boolean to store the direction of the movement
     */
    bool m_goingForward;

public:
    Vertical();
    virtual std::string getName() { return "Vertical"; }
    virtual void move(ngl::Transformation &_transform, ngl::Vec4 &_velocity, ngl::Vec4 &_angularVelocity, degreesOfFreedom &_dof);

};

#endif // VERTICAL_H

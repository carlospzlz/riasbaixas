#ifndef DIAGONAL_H
#define DIAGONAL_H

/**
 * @file Diagonal.h
 * @brief diagonal movement on the sea
 */
#include "Behaviour.h"

/**
 * @class Diagonal
 * @brief Behaviour of diagonal movement on the sea
 */
class Diagonal : public Behaviour
{

private:
    /**
     * @brief angle where the prow of the object is pointing
     */
    int m_angle;
    /**
     * @brief quadrant where the sense of the diagonal points to.
     * Example: m_quadrant=1 -> m_angle->45
     */
    int m_quadrant;

public:
    Diagonal();
    virtual std::string getName() { return "Diagonal"; }
    virtual void move(ngl::Transformation &_transform, ngl::Vec4 &_velocity, ngl::Vec4 &_angularVelocity, degreesOfFreedom &_dof);
};
#endif // DIAGONAL_H

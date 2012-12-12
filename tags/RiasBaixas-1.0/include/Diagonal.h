#ifndef DIAGONAL_H
#define DIAGONAL_H

/**
 * @file Diagonal.h
 * @brief diagonal movement on the sea
 */
#include "Controller.h"

/**
 * @class Diagonal
 * @brief Behaviour of diagonal movement on the sea
 */
class Diagonal : public Controller
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
    virtual void move();
};
#endif // DIAGONAL_H

#ifndef DIAGONAL_H
#define DIAGONAL_H

#include "Controller.h"


class Diagonal : public Controller
{

private:
    int m_angle;
    int m_quadrant;
    int m_ticksFloating;

public:
    Diagonal();
    virtual void move();
};
#endif // DIAGONAL_H

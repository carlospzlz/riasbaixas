#ifndef HORIZONTAL_H
#define HORIZONTAL_H

#include "Controller.h"

class Horizontal : public Controller
{

private:
    bool m_goingRight;

public:
    Horizontal();
    virtual void move();

};

#endif // HORIZONTAL_H

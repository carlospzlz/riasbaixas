#ifndef VERTICAL_H
#define VERTICAL_H

#include "Controller.h"

class Vertical : public Controller
{

private:
    bool m_goingForward;

public:
    Vertical();
    virtual void move();

};

#endif // VERTICAL_H

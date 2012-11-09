#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "DynamicSeaElement.h"


class Controller
{

public:
    void handleMovement(DynamicSeaElement &_dse);
    void handleCollision(DynamicSeaElement &_dse);

};

#endif // CONTROLLER_H

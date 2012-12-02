#ifndef CONTROLLERMANAGER_H
#define CONTROLLERMANAGER_H

#include "Controller.h"

class ControllerManager
{

private:
    std::vector<Controller*> m_controllers;

public:
    void addController(Controller* _c) { m_controllers.push_back(_c); }
    void updateControllers();

};

#endif // CONTROLLERMANAGER_H

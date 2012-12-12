#ifndef CONTROLLERMANAGER_H
#define CONTROLLERMANAGER_H

/**
 * @file ControllerManager.h
 * @brief This class stores all the AI of the game. It manages the controlles and is in
 * charge of update all of them
 */
#include "Controller.h"

/**
 * @class ControllerManager
 * @brief This class stores all the AI of the game. It manages the controlles and is in
 * charge of update all of them
 */
class ControllerManager
{

private:
    /**
     * @brief all the controllers
     */
    std::vector<Controller*> m_controllers;

public:
    ~ControllerManager();
    void addController(Controller* _c) { m_controllers.push_back(_c); }
    /**
     * @brief update all the controllers, it means that every one of them will move
     * the world object that has referenced
     */
    void updateControllers();

};

#endif // CONTROLLERMANAGER_H

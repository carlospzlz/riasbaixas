#include "ControllerManager.h"


ControllerManager::~ControllerManager()
{
    std::cout << "ControllerManager: Deleting AI..." << std::endl;
    std::vector<Controller*>::iterator endController = m_controllers.end();
    for(std::vector<Controller*>::iterator currentController=m_controllers.begin(); currentController!=endController;++currentController)
    {
        delete (*currentController);
    }
}

void ControllerManager::updateControllers()
{
    std::vector<Controller*>::iterator endController = m_controllers.end();
    for(std::vector<Controller*>::iterator currentController=m_controllers.begin(); currentController!=endController;++currentController)
    {
        if ((*currentController)->isActive())
            (*currentController)->move();
    }
}

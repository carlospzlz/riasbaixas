#include "ControllerManager.h"


void ControllerManager::updateControllers()
{
    std::vector<Controller*>::iterator lastController = m_controllers.end();
    for(std::vector<Controller*>::iterator currentController=m_controllers.begin(); currentController!=m_controllers.end();++currentController)
    {
        if ((*currentController)->isActive())
            (*currentController)->move();
    }
}

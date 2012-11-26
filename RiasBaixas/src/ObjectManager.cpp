#include "ObjectManager.h"

#include "SpeedBoat.h"


void ObjectManager::createTestLevel()
{
    Object *o1 = new Object();
    o1->setPosition(ngl::Vec4(0,2,-2,1));
    m_objects.push_back(o1);

    Object *o2 = new Object();
    o2->setPosition(ngl::Vec4(0,-2,-2,1));
    m_objects.push_back(o2);

}

void ObjectManager::updateObjects()
{
    std::vector<Object*>::iterator lastO = m_objects.end();
    for(std::vector<Object*>::iterator currentO=m_objects.begin(); currentO!=lastO; ++currentO)
    {
        (*currentO)->update(m_centralObject->getPosition().m_z, m_far);
    }
}

void ObjectManager::checkCollisions()
{
    checkCollisionsWithSeaLimits();
}

void ObjectManager::checkCollisionsWithSeaLimits()
{
    std::vector<Object*>::iterator lastO = m_objects.end();
    for(std::vector<Object*>::iterator currentO=m_objects.begin(); currentO!=lastO; ++currentO)
    {
        if ((*currentO)->getPosition().m_x<-SEA_WIDTH/2.0)
        {
            (*currentO)->getDOF().left = false;
            //(*currentO)->setPosition((*currentO)->getPreviousPos());
        }
        else
           (*currentO)->getDOF().left = true;

        if ((*currentO)->getPosition().m_x>SEA_WIDTH/2.0)
        {
            (*currentO)->getDOF().right = false;
            //(*currentO)->setPosition((*currentO)->getPreviousPos());
        }
        else
           (*currentO)->getDOF().right = true;
    }
}

#include "ObjectManager.h"

#include "SpeedBoat.h"

ObjectManager::~ObjectManager()
{
    destroyTheWorld();
}

void ObjectManager::destroyTheWorld()
{
    std::cout << "ObjectManager: Destroying the world..." << std::endl;
    std::vector<Object*>::iterator endO = m_objects.end();
    for(std::vector<Object*>::iterator currentO=m_objects.begin(); currentO!=endO; ++currentO)
    {
        delete (*currentO);
    }
}

void ObjectManager::createTestLevel()
{
    Object *o1 = new Object();
    o1->setPosition(ngl::Vec4(0,2,-2,1));
    m_objects.push_back(o1);

    Object *o2 = new Object();
    o2->setPosition(ngl::Vec4(0,-2,-2,1));
    m_objects.push_back(o2);

}

void ObjectManager::checkActiveObjects()
{
    std::vector<Object*>::iterator lastO = m_objects.end();
    for(std::vector<Object*>::iterator currentO=m_objects.begin(); currentO!=lastO; ++currentO)
    {
        (*currentO)->checkActive(m_centralObject->getPosition().m_z, m_far);
    }
}

void ObjectManager::checkCollisions(PhysicsEngine *_physicsEngine)
{

    clearCollisionInformation();

    std::vector<Object*>::iterator endO = m_objects.end();
    std::vector<Object*>::iterator lastO = endO-1;

    for(std::vector<Object*>::iterator o1=m_objects.begin(); o1!=lastO; ++o1)
    {
        if ((*o1)->isActive())
        {
            for(std::vector<Object*>::iterator o2=o1+1; o2!= endO; ++o2)
            {
                if ((*o2)->isActive())
                {
                    _physicsEngine->checkCollision(*o1,*o2);
                }
            }
        }
    }

    checkCollisionsWithSeaLimits();
}

void ObjectManager::clearCollisionInformation()
{
    std::vector<Object*>::iterator endO = m_objects.end();
    for(std::vector<Object*>::iterator currentO=m_objects.begin(); currentO!=endO; ++currentO)
    {
        if ((*currentO)->isActive())
        {
            (*currentO)->setCollided(false);
            (*currentO)->getDOF().up = true;
            (*currentO)->getDOF().down = true;
            (*currentO)->getDOF().left = true;
            (*currentO)->getDOF().right = true;
            (*currentO)->getDOF().forward = true;
            (*currentO)->getDOF().backward = true;
        }
    }
}

void ObjectManager::checkCollisionsWithSeaLimits()
{
    std::vector<Object*>::iterator lastO = m_objects.end();
    for(std::vector<Object*>::iterator currentO=m_objects.begin(); currentO!=lastO; ++currentO)
    {
        if ((*currentO)->isActive())
        {
            if ((*currentO)->getPosition().m_x<-SEA_WIDTH/2.0)
            {
                (*currentO)->getDOF().left = false;
                (*currentO)->setCollided(true);
            }

            if ((*currentO)->getPosition().m_x>SEA_WIDTH/2.0)
            {
                (*currentO)->getDOF().right = false;
                (*currentO)->setCollided(true);
            }
        }
    }
}

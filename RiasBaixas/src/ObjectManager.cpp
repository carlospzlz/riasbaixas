#include "ObjectManager.h"

#include "SpeedBoat.h"
#include "MusselFarm.h"


void ObjectManager::addStaticObject(StaticObject *_so)
{
    m_staticObjects.push_back(_so);
    m_objects.push_back(_so);
}

void ObjectManager::addDynamicObject(DynamicObject *_do)
{
    m_dynamicObjects.push_back(_do);
    m_objects.push_back(_do);
}

void ObjectManager::createTestLevel()
{
    addStaticObject(new MusselFarm(ngl::Vec3(-2,0,0)));
    addStaticObject(new MusselFarm(ngl::Vec3(2,0,0)));
}

void ObjectManager::moveObjects()
{
    std::vector<DynamicObject*>::iterator lastDO = m_dynamicObjects.end();
    for(std::vector<DynamicObject*>::iterator currentDO=m_dynamicObjects.begin(); currentDO!=lastDO; ++currentDO)
    {
        (*currentDO)->move();
    }
}

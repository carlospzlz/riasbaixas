#include "ObjectManager.h"

#include "SpeedBoat.h"


void ObjectManager::createTestLevel()
{
    Object *o1 = new Object();
    o1->setPosition(ngl::Vec3(0,2,-2));
    m_objects.push_back(o1);

    Object *o2 = new Object();
    o2->setPosition(ngl::Vec3(0,-2,-2));
    m_objects.push_back(o2);

}

void ObjectManager::updateObjects()
{
    std::vector<Object*>::iterator lastO = m_objects.end();
    for(std::vector<Object*>::iterator currentO=m_objects.begin(); currentO!=lastO; ++currentO)
    {
        (*currentO)->update(m_centreObject->getPosition().m_z, m_far);
    }
}

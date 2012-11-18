#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "Sea.h"
#include "Object.h"
#include "StaticObject.h"
#include "DynamicObject.h"
#include "SourceManager.h"

typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

class ObjectManager
{

private:
    Sea *m_sea;
    std::vector<Object*> m_objects;
    std::vector<StaticObject*> m_staticObjects;
    std::vector<DynamicObject*> m_dynamicObjects;

public:
    void setSea(Sea *_sea) { m_sea = _sea; }
    void addStaticObject(StaticObject *_so);
    void addDynamicObject(DynamicObject *_do);
    Sea* getSea() { return m_sea; }
    std::vector<StaticObject*> getStaticObjects() { return m_staticObjects; }
    std::vector<DynamicObject*> getDynamicObjects() { return m_dynamicObjects; }
    std::vector<Object*> getObjects() { return m_objects; }
    void processObjects(){}
    void destroyTheWorld();
    void createTestLevel();
    void moveObjects();

};

#endif // OBJECTMANAGER_H

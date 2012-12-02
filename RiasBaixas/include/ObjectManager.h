#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "Sea.h"
#include "Object.h"
#include "SourceManager.h"
#include "PhysicsEngine.h"

typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

class ObjectManager
{

private:
    Sea m_sea;
    std::vector<Object*> m_objects;
    Object *m_centralObject;
    //the clipping is both made with the far plane, thus we have frontal and back cameras
    float m_far;
    void checkCollisionsWithSeaLimits();
    void clearCollisionInformation();

public:
    void setSea(Sea _sea) { m_sea = _sea; }
    void addObject(Object* _o) { m_objects.push_back(_o);}
    void setCentralObject(Object* _o) { m_centralObject = _o; }
    void setFar(float _far) { m_far = _far; }
    const Sea& sea() { return m_sea; }
    std::vector<Object*>& objects() { return m_objects; }
    void checkActiveObjects();
    void checkCollisions(PhysicsEngine *_physicsEngine);
    //void checkCollisions(PhysicsEngine _physicsEngine);
    void destroyTheWorld();
    void createTestLevel();

};

#endif // OBJECTMANAGER_H

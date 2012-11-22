#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "Sea.h"
#include "Object.h"
#include "SourceManager.h"

typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

class ObjectManager
{

private:
    Sea *m_sea;
    std::vector<Object*> m_objects;
    Object *m_centreObject;
    //the clipping is both made with the far plane, thus we have frontal and back cameras
    float m_far;

public:
    void setSea(Sea *_sea) { m_sea = _sea; }
    void addObject(Object *_o) { m_objects.push_back(_o);}
    void setCentreObject(Object *_o) { m_centreObject = _o; }
    void setFar(float _far) { m_far = _far; }
    Sea* getSea() { return m_sea; }
    std::vector<Object*> getObjects() { return m_objects; }
    //void checkCollisions(PhysicsEngine _physicsEngine);
    void updateObjects();
    void destroyTheWorld();
    void createTestLevel();

};

#endif // OBJECTMANAGER_H

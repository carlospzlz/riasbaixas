#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

/**
 * @file ObjectManager.h
 * @brief This class is the responsable to store and manage all the
 * objects in the game world
 */
#include "Sea.h"
#include "Object.h"
#include "SourceManager.h"
#include "PhysicsEngine.h"

/**
 * @class ObjectManager
 * @brief This class is the responsable to store and manage all the
 * objects in the game world
 */
class ObjectManager
{

private:
    /**
     * @brief background of the game scene
     */
    Sea* m_sea;
    /**
     * @brief all the objects in the world
     */
    std::vector<Object*> m_objects;
    /**
     * @brief the main objec which is controlled by the user
     */
    Object *m_centralObject;
    /**
     * @brief the distance from the eye (which is around the main object)
     * to the far clipping plane
     */
    //the clipping is both made with the far plane, thus we have frontal and back cameras
    float m_far;
    /**
     * @brief clamp the collisions to the border of the sea
     */
    void checkCollisionsWithSeaLimits();
    /**
     * @brief clear all the data about collisions that the objects store
     */
    void clearCollisionInformation();

public:
    ~ObjectManager();
    void setSea(Sea* _sea) { m_sea = _sea; }
    void addObject(Object* _o) { m_objects.push_back(_o);}
    void setCentralObject(Object* _o) { m_centralObject = _o; }
    void setFar(float _far) { m_far = _far; }
    const Sea& sea() { return *m_sea; }
    std::vector<Object*>& objects() { return m_objects; }
    /**
     * @brief check all the objects and activate those ones which are
     * inside the interval -far to +far centered in the main object
     */
    void checkActiveObjects();
    /**
     * @brief check the collisions among all the objects in the world
     * using a physicsEngine. This method is not aware of which specific
     * physics engine is used.
     */
    void checkCollisions(PhysicsEngine *_physicsEngine);
    /**
     * @brief this method delete all the stored objects, thus destroy the
     * complete and current world. The game world, not the real world, so
     * don't worry.
     */
    void destroyTheWorld();
    void createTestLevel();

};

#endif // OBJECTMANAGER_H

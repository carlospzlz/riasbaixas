#ifndef GAMEPLAY_H
#define GAMEPLAY_H

/**
 * @file GamePlay.h
 * @brief This is the specific state corresponding to the game play
 */

#include "GameState.h"
#include "GameMenu.h"

/**
 * @class GamePlay
 * @brief This is the specific state corresponding to the game play
 */

class GamePlay : public GameState
{

private:
    /**
     * @brief check which objects are active
     */
    void checkActiveObjects(std::vector<Object*> &_objects, ngl::Camera *_cam);
    /**
     * @brief this method notifies to all the objects and requests update their state (observer pattern)
     */
    void updateObjects(std::vector<Object*> &_objects);
    /**
     * @brief check all the possible collisions using a provided specific PhysicsEngine
     */
    void checkCollisions(std::vector<Object*> &_objects, const Sea &_sea, PhysicsEngine *_physicsEngine);
    /**
     * @brief clear the information of the objects used for collisions
     */
    void clearCollisionInformation(std::vector<Object*> &_objects);
    /**
     * @brief check the collisions with the sea limits
     */
    void checkCollisionsWithSeaLimits(std::vector<Object*> &_objects, const Sea &_sea);
    /**
     * @brief delete all the memory dinamically allocated
     */
    void releaseMemory(std::vector<Object*> &_objects);

public:
    /**
     * @brief run the game play
     */
    virtual GameState *run(Renderer &_renderer);

};

#endif // GAMEPLAY_H

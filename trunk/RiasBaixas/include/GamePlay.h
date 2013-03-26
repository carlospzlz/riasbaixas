#ifndef GAMEPLAY_H
#define GAMEPLAY_H


#include "GameState.h"
#include "GameMenu.h"

class GamePlay : public GameState
{

private:
    void checkActiveObjects(std::vector<Object*> &_objects, ngl::Camera *_cam);
    void updateObjects(std::vector<Object*> &_objects);
    void checkCollisions(std::vector<Object*> &_objects, const Sea &_sea, PhysicsEngine *_physicsEngine);
    void clearCollisionInformation(std::vector<Object*> &_objects);
    void checkCollisionsWithSeaLimits(std::vector<Object*> &_objects, const Sea &_sea);
    void releaseMemory(std::vector<Object*> &_objects);

public:
    virtual GameState *run(Renderer &_renderer);

};

#endif // GAMEPLAY_H

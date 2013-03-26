#ifndef GAMESTORY_H
#define GAMESTORY_H

#include "GameState.h"
#include "GamePlay.h"

class GameStory : public GameState
{
private:
public:
    virtual GameState *run(Renderer &_renderer);
};

#endif // GAMESTORY_H

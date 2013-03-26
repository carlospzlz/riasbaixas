#ifndef GAMEMENU_H
#define GAMEMENU_H

#include "GameState.h"
#include "GameStory.h"

class GameMenu : public GameState
{
private:
public:
    virtual GameState *run(Renderer &_renderer);
};

#endif // GAMEMENU_H

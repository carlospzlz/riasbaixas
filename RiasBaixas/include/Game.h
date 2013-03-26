#ifndef GAME_H
#define GAME_H

#include "GameMenu.h"

class Game
{

private:
    GameState *m_gameState;

public:
    Game() { m_gameState = new GameMenu(); }
    void setState(GameState *_gameState) { m_gameState=_gameState; }
    GameState *getGameState() { return m_gameState; }
    GameState *run(Renderer &_renderer) { return m_gameState->run(_renderer); }

};

#endif // GAME_H

#ifndef GAME_H
#define GAME_H

/**
 * @file Game.h
 * @brief This is the base class of the application which starts the game
 */

#include "GameMenu.h"

/**
 * @class Game
 * @brief This is the base class of the application which starts the game
 */

class Game
{

private:
    /**
     * @brief The current state of the game
     */
    GameState *m_gameState;

public:
    Game() { m_gameState = new GameMenu(); }
    /**
     * @brief set the state of the game
     */
    void setState(GameState *_gameState) { m_gameState=_gameState; }
    /**
     * @brief get the sate of the game
     */
    GameState *getGameState() { return m_gameState; }
    /**
     * @brief run the whole game
     */
    GameState *run(Renderer &_renderer) { return m_gameState->run(_renderer); }

};

#endif // GAME_H

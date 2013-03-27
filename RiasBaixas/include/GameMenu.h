#ifndef GAMEMENU_H
#define GAMEMENU_H

/**
 * @file GameMenu.h
 * @brief This is the specific state corresponding to the menu of the game
 */

#include "GameState.h"
#include "GameStory.h"

/**
 * @class GameMenu
 * @brief This is the specific state corresponding to the menu of the game
 */

class GameMenu : public GameState
{
private:
public:
    /**
     * @brief run the menu of the game
     */
    virtual GameState *run(Renderer &_renderer);
};

#endif // GAMEMENU_H

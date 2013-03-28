#ifndef GAMESTORY_H
#define GAMESTORY_H

/**
 * @file GameStory.h
 * @brief This class performs the operations related with the story and contextualization of the game
 * before stating the game play
 */

#include "GameState.h"
#include "GamePlay.h"

/**
 * @file GameStory
 * @brief This class performs the operations related with the story and contextualization of the game
 * before stating the game play
 */

class GameStory : public GameState
{
private:
public:
    /**
     * @brief run the story
     */
    virtual GameState *run(Renderer &_renderer);
};

#endif // GAMESTORY_H

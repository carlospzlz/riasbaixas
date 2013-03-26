#include "Game.h"

int main()
{
    Game myGame = Game();
    Renderer myRenderer = Renderer();

    //The graphic context remains the same for all states!
    myRenderer.initGLContext();

    GameState* nextGameState = myGame.getGameState();

    while (nextGameState)
    {
        nextGameState = myGame.run(myRenderer);
        myGame.setState(nextGameState);
    }

    return 0;
}

#include "GameMenu.h"

GameState *GameMenu::run(Renderer &_renderer)
{

    playerOptions myPlayerOptions;
    PlayerControls myPlayerControls;
    Utilities myUtilities;

    SDL_Event myEvent;
    bool go = false;
    GLuint textureID;

    _renderer.loadTexture("images/riasBaixasCover.jpg", textureID);

    while (!(go=myPlayerOptions.enter) && myPlayerOptions.running)
    {
        myUtilities.readPlayerInput(myPlayerControls, myPlayerOptions, _renderer.isFullScreen());
        myUtilities.setWindow(_renderer, myPlayerOptions);

        _renderer.renderFrame(textureID);

    }

    if (go)
    {
        _renderer.fadeOut();
        return (new GameStory());
    }
    else
        return NULL;
}

#include "GameMenu.h"

GameState *GameMenu::run(Renderer &_renderer)
{

    playerOptions myPlayerOptions;
    PlayerControls myPlayerControls;
    Utilities myUtilities;

    bool go = false;
    GLuint textureID;

    _renderer.loadTexture("images/riasBaixasCover.jpg", textureID);

    while (!(go=myPlayerOptions.enter) && myPlayerOptions.running && !myPlayerOptions.changeState)
    {
        myUtilities.readPlayerInput(myPlayerControls, myPlayerOptions, _renderer.isFullScreen());
        myUtilities.setWindow(_renderer, myPlayerOptions);

        _renderer.renderFrame(textureID);

    }

    if (!myPlayerOptions.running || myPlayerOptions.changeState)
        return NULL;

    _renderer.fadeOut();
    return (new GameStory());
}

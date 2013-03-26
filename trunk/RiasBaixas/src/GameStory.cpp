#include "GameStory.h"

GameState *GameStory::run(Renderer &_renderer)
{

    //story here
    playerOptions myPlayerOptions;
    PlayerControls myPlayerControls;
    Utilities myUtilities;

    bool go = false;
    GLuint textureID;

    _renderer.loadTexture("images/riasBaixasStory.jpg", textureID);

    while (!(go=myPlayerOptions.enter || myPlayerOptions.changeState) && myPlayerOptions.running)
    {
        myUtilities.readPlayerInput(myPlayerControls, myPlayerOptions, _renderer.isFullScreen());
        myUtilities.setWindow(_renderer, myPlayerOptions);

        _renderer.renderFrame(textureID);

    }

    if (!myPlayerOptions.running)
        return NULL;

    //_renderer.fadeOut();

    _renderer.loadTexture("images/riasBaixasDrive.jpg", textureID);
    int nFrames = 7*30;
    for(int i=0;i<nFrames;++i)
    {
        myUtilities.readPlayerInput(myPlayerControls, myPlayerOptions, _renderer.isFullScreen());
        myUtilities.setWindow(_renderer, myPlayerOptions);

        _renderer.renderFrame(textureID);
        usleep(1000000/30);
    }

    _renderer.fadeOut();

    return (new GamePlay());

}

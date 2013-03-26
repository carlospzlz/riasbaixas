#include "Utilities.h"


void Utilities::readPlayerInput(PlayerControls &_playerControls, playerOptions &_playerOptions, bool _isfullScreen)
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {

            case SDL_QUIT:
            _playerOptions.running = false;
            break;

            case SDL_WINDOWEVENT:
            _playerOptions.resizeWindow = true;

            case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                {
                if (_isfullScreen)
                    _playerOptions.restoreWindow = true;
                else
                    _playerOptions.changeState = true;
                }
                break;

                case SDLK_RIGHT:
                _playerControls.setRight(true);
                break;

                case SDLK_LEFT:
                _playerControls.setLeft(true);
                break;

                case SDLK_SPACE:
                _playerControls.setSpeedUp(true);
                break;

                case SDLK_BACKSPACE:
                _playerOptions.backCamera = true;
                break;

                case SDLK_c:
                _playerOptions.changeCameraPressed = true;
                break;

                case SDLK_0:
                _playerOptions.debugMode = 0;
                break;

                case SDLK_1:
                _playerOptions.debugMode = 1;
                break;

                case SDLK_2:
                _playerOptions.debugMode = 2;
                break;

                case SDLK_PAUSE:
                _playerOptions.pause = !_playerOptions.pause;
                break;

                case SDLK_F11:
                if (!_isfullScreen)
                    _playerOptions.changeToFullScreen = true;
                else
                    _playerOptions.restoreWindow = true;
                break;

                case SDLK_RETURN:
                _playerOptions.enter = true;
                break;

           }
            break;

            case SDL_KEYUP:
            switch(event.key.keysym.sym)
            {
                case SDLK_RIGHT:
                _playerControls.setRight(false);
                break;

                case SDLK_LEFT:
                _playerControls.setLeft(false);
                break;

                case SDLK_SPACE:
                _playerControls.setSpeedUp(false);
                break;

                case SDLK_BACKSPACE:
                _playerOptions.backCamera = false;
                break;

                case SDLK_c:
                {
                _playerOptions.changeCameraPressed = false;
                _playerOptions.possibleChangeCamera = true;
                }
                break;

                case SDLK_RETURN:
                _playerOptions.enter = false;
                break;
            }
            break;
        }
    }

}


void Utilities::setWindow(Renderer &_renderer, playerOptions &_playerOptions)
{
    if (_playerOptions.resizeWindow)
    {
        _renderer.resizeWindow();
        _playerOptions.resizeWindow = false;
    }
    if (_playerOptions.changeToFullScreen)
    {
        _renderer.fullScreen();
        _playerOptions.changeToFullScreen = false;
    }
    if (_playerOptions.restoreWindow)
    {
        _renderer.restoreWindow();
        _playerOptions.restoreWindow = false;
    }

}


void Utilities::setCamera(CameraSet &_cameraSet, const Renderer &_renderer, playerOptions &_playerOptions)
{
    if (_playerOptions.resizeWindow)//|| _playerOptions.changeToFullScreen || _playerOptions.restoreWindow)
    {
        _cameraSet.setShape(_renderer.getWindowWidth(), _renderer.getWindowHeight());
        _playerOptions.resizeWindow = false;
    }

    if (_playerOptions.backCamera)
    {
        if (!_cameraSet.isBackCameraActive())
            _cameraSet.changeToBackCamera();
    }
    else
    {
        if (_cameraSet.isBackCameraActive())
            _cameraSet.leaveBackCamera();
    }

    if (_playerOptions.changeCameraPressed && _playerOptions.possibleChangeCamera && !_cameraSet.isBackCameraActive())
    {
        _cameraSet.nextCamera();
        _playerOptions.possibleChangeCamera = false;
    }

}

void Utilities::regulateFPS(Uint32 &_startingTick, int &_frameCounter, Uint32 &_lastStartingSecond, int &_fps, int max_fps)
{
    //calculate current frames per second
    if (SDL_GetTicks()-_lastStartingSecond > 1000)
    {
        _lastStartingSecond = SDL_GetTicks();
        _fps = _frameCounter;
        _frameCounter = 0;
    }
    else
        ++_frameCounter;

    //Adjust frames per second
    if (1000/max_fps>(int)(SDL_GetTicks()-_startingTick))
        SDL_Delay(1000/max_fps-(SDL_GetTicks()-_startingTick));

}

void Utilities::initPlayerOptions(playerOptions &_playerOptions)
{

     _playerOptions.running = true;
     _playerOptions.changeState = false;
     _playerOptions.debugMode = 0;
     _playerOptions.possibleChangeCamera = true;
     _playerOptions.changeCameraPressed = false;
     _playerOptions.backCamera = false;
     _playerOptions.pause = false;
     _playerOptions.resizeWindow = false;
     _playerOptions.changeToFullScreen = false;
     _playerOptions.restoreWindow = false;
     _playerOptions.enter = false;

}

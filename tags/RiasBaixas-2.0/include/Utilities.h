#ifndef UTILITIES_H
#define UTILITIES_H

/**
 * @file Utilities.h
 * @brief this class groups some useful functionalities used by the Game Manager
 */
#include "PlayerControls.h"
#include "CameraSet.h"
#include "Renderer.h"

/**
 * @struct playerOptions
 * @brief this struct contains the options of the game that the player
 * might manipulate
 */
struct playerOptions
{
    bool running;
    bool changeState;
    int debugMode;
    bool possibleChangeCamera;
    bool changeCameraPressed;
    bool backCamera;
    bool pause;
    bool resizeWindow;
    bool changeToFullScreen;
    bool restoreWindow;
    bool enter;
};

/**
 * @class Utilities
 * @brief this class groups some useful functionalities used by the Game Manager
 */
class Utilities
{

public:
    /**
     * @brief reads the input of the player through the standard input
     */
    void readPlayerInput(PlayerControls &_playerControls, playerOptions &_playerOptions, bool _isfullScreen);
    /**
     * @brief sets the current camera according with the options of the player
     */
    void setCamera(CameraSet &_cameraSet, const Renderer &_renderer, playerOptions &_playerOptions);
    /**
     * @brief sets the window according with the options of the player
     */
    void setWindow(Renderer &_renderer, playerOptions &_playerOptions);
    /**
     * @brief regulates the frames per second rate of the game play
     */
    void regulateFPS(Uint32 &_startingTick, int &_frameCounter, Uint32 &_lastStartingSecond, int &_fps, int max_fps);
    /**
     * @brief initializes the values of the fields of a playerOptions struct
     */
    void initPlayerOptions(playerOptions &_playerOptions);
};

#endif // UTILITIES_H

#ifndef GAMESTATE_H
#define GAMESTATE_H

/**
 * @file GameState.h
 * @brief This is the abstract class for the state of the game
 */

#include <ngl/Obj.h>
//glew must be included first!
#include <iostream>
#include <ngl/VAOPrimitives.h>
#include <ngl/TransformStack.h>
#include "Renderer.h"
#include "SourceStore.h"
#include "SpeedBoat.h"
#include "PoliceBoat.h"
#include "Sea.h"
#include "Object.h"
#include "Behaviour.h"
#include "PlayerControls.h"
#include "Floating.h"
#include "TXTParser.h"
#include "Diagonal.h"
#include "Floating.h"
#include "Horizontal.h"
#include "Vertical.h"
#include "PhysicsEngine.h"
#include "BSpherePE.h"
#include "Utilities.h"

/**
 * @class GameState
 * @brief This is the abstract class for the state of the game
 */

class GameState
{

public:
    /**
     * @brief Virtual method which should be implemented by specific states
     */
    virtual GameState *run(Renderer &_renderer) = 0;

};

#endif // GAMESTATE_H

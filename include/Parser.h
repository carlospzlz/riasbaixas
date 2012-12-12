#ifndef PARSER_H
#define PARSER_H

/**
 * @file Parser.h
 * @brief this class parses a file and load the needed data for creating the world
 */
#include "SourceManager.h"
#include "ControllerManager.h"
#include "ObjectManager.h"
#include "Object.h"
#include "Sea.h"
#include "SpeedBoat.h"
#include "Controller.h"
#include "Floating.h"
#include "Horizontal.h"
#include "Diagonal.h"
#include "Vertical.h"

/**
 * @class Parser
 * @brief this class parses a file and load the needed data for creating the world
 */
class Parser
{

public:
    /**
     * @brief load the basic sources for starting the game
     */
    virtual bool loadBasicSources(SourceManager &_sourceManager){};
    //void loadRadioConversation();
    /**
     * @brief load specific sources needed for a level
     */
    virtual bool loadLevelSources(int _level, SourceManager &_sourceManager){};
    /**
     * @brief load specific objects for one specific map
     */
    virtual bool loadMap(int _map, ObjectManager &_objectManager, ControllerManager &_controllerManager, SourceManager &_sourceManager){};

};

#endif // PARSER_H

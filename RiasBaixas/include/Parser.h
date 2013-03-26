#ifndef PARSER_H
#define PARSER_H

/**
 * @file Parser.h
 * @brief this class parses a file and load the needed data for creating the world
 */
#include "SourceStore.h"
#include "Object.h"
#include "Sea.h"
#include "Behaviour.h"
#include "Floating.h"
#include "Horizontal.h"
#include "Diagonal.h"
#include "Vertical.h"
#include "PlayerControls.h"

/**
 * @class Parser
 * @brief this class parses a file and load the needed data for creating the world
 */
class Parser
{

protected:
    const static std::string s_mapsPath;
    const static std::string s_behaviourParametersPath;

public:
    /**
     * @brief load the basic sources for starting the game
     */
    virtual bool loadSources(SourceStore &_sourceStore) = 0;
    /**
     * @brief load specific objects for one specific map
     */
    virtual bool loadMap(int _map, Sea &_sea, std::vector<Object*> &_objects, SourceStore &_sourceStore) = 0;
    /**
     * @brief load parameters of a general Behaviour
     */
    virtual bool loadBehaviourParameters(Behaviour *_behaviour) = 0;
    /**
     * @brief load parameters of the specific behaviour PlayerControls
     */
    virtual bool loadPlayerControlsParameters(PlayerControls *_playerControls) = 0;

};

#endif // PARSER_H

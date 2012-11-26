#ifndef TXTPARSER_H
#define TXTPARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>

#include "Parser.h"

#define TXTPARSER_MAPS_PATH "maps/"


class TxtParser : public Parser
{

    typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

private:
    bool loadSea(tokenizer::iterator _currentParameter, ObjectManager &_objectManager, SourceManager &_sourceManager);
    bool loadMusselFarm(tokenizer::iterator _currentParameter, ObjectManager &_objectManager, SourceManager &_sourceManager);
    bool loadFisherBoat(tokenizer::iterator _currentParameter, ObjectManager &_objectManager, SourceManager &_sourceManager);
    bool loadController(tokenizer::iterator _currentParameter, Object *_object);

public:
    bool loadBasicSources(SourceManager &_souceManager);
    bool loadLevelSources(int _level, SourceManager &_sourceManager);
    bool loadMap(int _map, ObjectManager &_objectManager, SourceManager &_sourceManager);
};

#endif // TXTPARSER_H

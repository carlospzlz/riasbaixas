#ifndef TXTPARSER_H
#define TXTPARSER_H

/**
 * @file TXTParser.h
 * @brief specific Parser for .txt files
 */
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>

#include "Parser.h"

/**
 * @class TXTParser
 * @brief specific Parser for .txt files
 */
class TXTParser : public Parser
{

    typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

private:
    static const std::string s_mapPath;

    bool loadSea(tokenizer::iterator _currentParameter, Sea &_sea, SourceStore &_sourceStore);
    bool loadMusselFarm(tokenizer::iterator _currentParameter, std::vector<Object*> &_objects, SourceStore &_sourceStore);
    bool loadFisherBoat(tokenizer::iterator _currentParameter, std::vector<Object*> &_objects, SourceStore &_sourceStore);
    bool loadBehaviour(tokenizer::iterator _currentParameter, Behaviour *&_behaviour);

public:
    bool loadSources(SourceStore &_sourceStore);
    bool loadMap(int _map, Sea &_sea, std::vector<Object*> &_objects, SourceStore &_sourceStore);
};

#endif // TXTPARSER_H

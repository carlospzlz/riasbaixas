#ifndef PARSER_H
#define PARSER_H

#include "SourceManager.h"

#include "ObjectManager.h"
#include "Sea.h"
#include "SpeedBoat.h"
#include "MusselFarm.h"
//#include "FisherBoat"

class Parser
{

public:
    virtual bool loadBasicSources(SourceManager *_sourceManager){};
    //void loadRadioConversation();
    virtual bool loadLevelSources(int _level, SourceManager *_sourceManager){};
    virtual bool loadMap(int _map, ObjectManager *_objectManager, SourceManager *_sourceManager){};

};

#endif // PARSER_H

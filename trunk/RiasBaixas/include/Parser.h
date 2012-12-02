#ifndef PARSER_H
#define PARSER_H

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
//#include "FisherBoat"

class Parser
{

public:
    virtual bool loadBasicSources(SourceManager &_sourceManager){};
    //void loadRadioConversation();
    virtual bool loadLevelSources(int _level, SourceManager &_sourceManager){};
    virtual bool loadMap(int _map, ObjectManager &_objectManager, ControllerManager &_controllerManager, SourceManager &_sourceManager){};

};

#endif // PARSER_H

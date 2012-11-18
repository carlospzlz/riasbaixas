#ifndef PARSER_H
#define PARSER_H

#include "SourceManager.h"

class Parser
{

public:
    void loadBasicSources(SourceManager _sourceManager){};
    //void loadRadioConversation();
    void loadFullSources(SourceManager _sourceManager){};
    void loadLevel(int _level, SourceManager _sourceManager){};

};

#endif // PARSER_H

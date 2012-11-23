#include "TxtParser.h"

bool TxtParser::loadLevelSources(int _level, SourceManager &_sourceManager)
{

}

bool TxtParser::loadMap(int _map, ObjectManager &_objectManager, SourceManager &_sourceManager)
{

    std::ifstream mapFile;
    std::ostringstream path;
    path << TXTPARSER_MAPSPATH << "map" << _map;

    std::cout << "Loading map " << path.str() << " ..." << std::endl;
    mapFile.open(path.str().c_str(),std::ifstream::in);

    if (!mapFile.is_open())
        {
            std::cout << "TXTPARSER ERROR: Map file " << mapFile << " not found" << std::endl;
            return false;
        }

    std::string lineBuffer;
    boost::char_separator<char> sep(" ");
    tokenizer::iterator currentToken;
    int lineNumber = 1;

    while(!mapFile.eof())
    {
        std::getline(mapFile,lineBuffer,'\n');
        if (lineBuffer.size() != 0)
        {
            tokenizer tokens(lineBuffer, sep);
            currentToken = tokens.begin();

            if (*currentToken == "Sea")
            {
                if (loadSea(currentToken, _objectManager, _sourceManager))
                    std::cout <<"TxtParser: in line " << lineNumber << ": Sea loaded" << std::endl;
                else
                    std::cout << "TxtParser: in line " << lineNumber << ": EXCEPTION: when loading Sea" << std::endl;
            }
            else if (*currentToken == "MusselFarm")
            {
                if (loadMusselFarm(currentToken, _objectManager, _sourceManager))
                    std::cout <<"TxtParser: in line " << lineNumber << ": MusselFarm loaded" << std::endl;
                else
                    std::cout << "TxtParser: in line " << lineNumber << ": EXCEPTION: when loading MusselFarm" << std::endl;
            }
            else if (*currentToken == "FisherBoat")
            {
                if (loadFisherBoat(currentToken, _objectManager, _sourceManager))
                    std::cout <<"TxtParser: in line " << lineNumber << ": FisherBoat loaded" << std::endl;
                else
                    std::cout << "TxtParser: in line " << lineNumber << ": EXCEPTION: when loading FisherBoat" << std::endl;

            }
            else
                std::cout << "TxtParser: In line " << lineNumber << ": WARNING: Unknown object" << std::endl;
        }
    ++lineNumber;
    }
    return true;
}

bool TxtParser::loadSea(tokenizer::iterator _currentParameter, ObjectManager &_objectManager, SourceManager &_sourceManager)
{
   try
   {
        float depth = boost::lexical_cast<float>(*++_currentParameter);

        Sea *sea = new Sea();
        sea->setDepth(depth);
        _objectManager.setSea(sea);
        return true;
    }
    catch (...)
    {
        return false;
    }
}

bool TxtParser::loadMusselFarm(tokenizer::iterator _currentParameter, ObjectManager &_objectManager, SourceManager &_sourceManager)
{
    try
    {
        std::string meshName = boost::lexical_cast<std::string>(*++_currentParameter);
        float x = boost::lexical_cast<float>(*++_currentParameter);
        float y = boost::lexical_cast<float>(*++_currentParameter);
        float z = boost::lexical_cast<float>(*++_currentParameter);

        Object *musselFarm = new Object();
        musselFarm->setMesh(_sourceManager.getMesh(meshName));
        musselFarm->setPosition(ngl::Vec4(x,y,z,1));
        _objectManager.addObject(musselFarm);

        return true;
    }
    catch (...)
    {
        return false;
    }
}

bool TxtParser::loadFisherBoat(tokenizer::iterator _currentParameter, ObjectManager &_objectManager, SourceManager &_sourceManager)
{

}

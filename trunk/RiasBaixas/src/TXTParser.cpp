#include "TXTParser.h"

bool TXTParser::loadBasicSources(SourceManager &_souceManager)
{

}

bool TXTParser::loadLevelSources(int _level, SourceManager &_sourceManager)
{

}

bool TXTParser::loadMap(int _map, ObjectManager &_objectManager, ControllerManager &_controllerManager, SourceManager &_sourceManager)
{

    std::ifstream mapFile;
    std::ostringstream path;
    path << TXTPARSER_MAPS_PATH << "map" << _map;

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
                if (loadFisherBoat(currentToken, _objectManager, _controllerManager, _sourceManager))
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

bool TXTParser::loadSea(tokenizer::iterator _currentParameter, ObjectManager &_objectManager, SourceManager &_sourceManager)
{
   try
   {
        float depth = boost::lexical_cast<float>(*++_currentParameter);

        Sea sea;
        sea.setDepth(depth);
        _objectManager.setSea(sea);
    }
    catch (...)
    {
        return false;
    }
    return true;
}

bool TXTParser::loadMusselFarm(tokenizer::iterator _currentParameter, ObjectManager &_objectManager, SourceManager &_sourceManager)
{
    try
    {
        float x = boost::lexical_cast<float>(*++_currentParameter);
        float y = boost::lexical_cast<float>(*++_currentParameter);
        float z = boost::lexical_cast<float>(*++_currentParameter);

        Object *musselFarm = new Object();
        musselFarm->setMesh(_sourceManager.getMesh("musselFarm"));
        musselFarm->setType(ot_musselFarm);
        musselFarm->setMass(0);
        musselFarm->setPosition(ngl::Vec4(x,y,z,1));
        _objectManager.addObject(musselFarm);
    }
    catch (...)
    {
        return false;
    }
    return true;
}

bool TXTParser::loadFisherBoat(tokenizer::iterator _currentParameter, ObjectManager &_objectManager,
                               ControllerManager &_controllerManager, SourceManager &_sourceManager)
{
    try
    {
        float x = boost::lexical_cast<float>(*++_currentParameter);
        float y = boost::lexical_cast<float>(*++_currentParameter);
        float z = boost::lexical_cast<float>(*++_currentParameter);

        Object *fisherBoat = new Object();
        fisherBoat->setMesh(_sourceManager.getMesh("fisherBoat"));
        fisherBoat->setPosition(ngl::Vec4(x,y,z,1));
        fisherBoat->setType(ot_fisherBoat);
        fisherBoat->setPrimName("teapot");

        if (!loadController(_currentParameter,_controllerManager,fisherBoat))
            return false;

        _objectManager.addObject(fisherBoat);
    }
    catch (...)
    {
        return false;
    }
    return true;
}

bool TXTParser::loadController(tokenizer::iterator _currentParameter, ControllerManager &_controllerManager, Object *_object)
{
    try
    {
        std::string controllerName = boost::lexical_cast<std::string>(*++_currentParameter);
        Controller *controller;

        if (controllerName == "Floating")
        {
            controller = new Floating();
            _object->setRotation(ngl::Vec4(0,rand()%360,0,1));
        }
        else if (controllerName == "Horizontal")
        {
            controller = new Horizontal();
        }
        else if (controllerName == "Vertical")
        {
            controller = new Vertical();
            _object->setRotation(ngl::Vec4(0,-90,0));
        }
            else if (controllerName == "Diagonal")
        {
        controller = new Diagonal();
        }

        controller->setControlledObject(_object);
        _controllerManager.addController(controller);
    }
    catch (...)
    {
        return false;
    }
    return true;
}
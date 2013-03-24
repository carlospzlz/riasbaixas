#include "TXTParser.h"

const std::string TXTParser::s_mapPath = "maps/";

bool TXTParser::loadSources(SourceStore &_sourceStore)
{
    _sourceStore.addMesh("speedboat", new ngl::Obj("models/speedboat.obj","textures/speedboat.jpg"));
    _sourceStore.addMesh("sea", new ngl::Obj("models/sea.obj","textures/sea.png"));
    _sourceStore.addMesh("musselFarm", new ngl::Obj("models/musselFarm.obj","textures/musselFarm.jpg"));
    _sourceStore.addMesh("fisherBoat", new ngl::Obj("models/fisherBoat.obj","textures/fisherBoat.jpg"));
}

bool TXTParser::loadMap(int _map, Sea &_sea, std::vector<Object*> &_objects, SourceStore &_sourceStore)
{

    std::ifstream mapFile;
    std::ostringstream path;
    path << s_mapPath << "map" << _map;

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
                if (loadSea(currentToken, _sea, _sourceStore))
                    std::cout <<"TXTParser: in line " << lineNumber << ": Sea loaded" << std::endl;
                else
                    std::cout << "TXTParser: in line " << lineNumber << ": EXCEPTION: when loading Sea" << std::endl;
            }
            else if (*currentToken == "MusselFarm")
            {
                if (loadMusselFarm(currentToken, _objects, _sourceStore))
                    std::cout <<"TXTParser: in line " << lineNumber << ": MusselFarm loaded" << std::endl;
                else
                    std::cout << "TXTParser: in line " << lineNumber << ": EXCEPTION: when loading MusselFarm" << std::endl;
            }
            else if (*currentToken == "FisherBoat")
            {
                if (loadFisherBoat(currentToken, _objects, _sourceStore))
                    std::cout <<"TXTParser: in line " << lineNumber << ": FisherBoat loaded" << std::endl;
                else
                    std::cout << "TXTParser: in line " << lineNumber << ": EXCEPTION: when loading FisherBoat" << std::endl;

            }
            else
                std::cout << "TXTParser: In line " << lineNumber << ": WARNING: Unknown object" << std::endl;
        }
    ++lineNumber;
    }
    return true;
}

bool TXTParser::loadSea(tokenizer::iterator _currentParameter, Sea &_sea, SourceStore &_sourceStore)
{
   try
   {
        float depth = boost::lexical_cast<float>(*++_currentParameter);

        _sea.setDepth(depth);
        _sea.setMesh(_sourceStore.getMesh("sea"));
    }
    catch (...)
    {
        return false;
    }
    return true;
}

bool TXTParser::loadMusselFarm(tokenizer::iterator _currentParameter, std::vector<Object*> &_objects, SourceStore &_sourceStore)
{
    try
    {
        float x = boost::lexical_cast<float>(*++_currentParameter);
        float y = boost::lexical_cast<float>(*++_currentParameter);
        float z = boost::lexical_cast<float>(*++_currentParameter);

        Object *musselFarm = new Object();
        musselFarm->setType(ot_musselFarm);
        musselFarm->setMesh(_sourceStore.getMesh("musselFarm"));
        musselFarm->setMass(0);
        musselFarm->setPosition(ngl::Vec4(x,y,z,1));
        _objects.push_back(musselFarm);
    }
    catch (...)
    {
        return false;
    }
    return true;
}

bool TXTParser::loadFisherBoat(tokenizer::iterator _currentParameter, std::vector<Object*> &_objects, SourceStore &_sourceStore)
{
    try
    {
        float x = boost::lexical_cast<float>(*++_currentParameter);
        float y = boost::lexical_cast<float>(*++_currentParameter);
        float z = boost::lexical_cast<float>(*++_currentParameter);

        Object *fisherBoat = new Object();
        fisherBoat->setMesh(_sourceStore.getMesh("fisherBoat"));
        fisherBoat->setPosition(ngl::Vec4(x,y,z,1));
        fisherBoat->setType(ot_fisherBoat);
        fisherBoat->setPrimName("teapot");

        Behaviour *behaviour;
        if (!loadBehaviour(_currentParameter, behaviour))
            return false;

        fisherBoat->setBehaviour(behaviour);
        _objects.push_back(fisherBoat);
        //fisherBoat->info();
    }
    catch (...)
    {
        return false;
    }
    return true;
}

bool TXTParser::loadBehaviour(tokenizer::iterator _currentParameter, Behaviour *&_behaviour)
{
    try
    {
        std::string behaviourName = boost::lexical_cast<std::string>(*++_currentParameter);

        if (behaviourName == "Floating")
        {
            _behaviour = new Floating();
            //_object->setRotation(ngl::Vec4(0,rand()%360,0,1));
        }
        else if (behaviourName == "Horizontal")
        {
            _behaviour = new Horizontal();
        }
        else if (behaviourName == "Vertical")
        {
            _behaviour = new Vertical();
            //_object->setRotation(ngl::Vec4(0,-90,0));
        }
            else if (behaviourName == "Diagonal")
        {
            _behaviour = new Diagonal();
        }

    }
    catch (...)
    {
        return false;
    }
    return true;
}

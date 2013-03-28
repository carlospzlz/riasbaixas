#include "TXTParser.h"


bool TXTParser::loadSources(SourceStore &_sourceStore)
{
    _sourceStore.addMesh("speedboat", new ngl::Obj("models/speedboat.obj","textures/speedboat2.jpg"));
    _sourceStore.addMesh("policeboat", new ngl::Obj("models/speedboat.obj","textures/policeboat.jpg"));
    _sourceStore.addMesh("sea", new ngl::Obj("models/sea.obj","textures/tiledSea.png"));
    _sourceStore.addMesh("musselFarm", new ngl::Obj("models/musselFarm.obj","textures/musselFarm.jpg"));
    _sourceStore.addMesh("fisherBoat", new ngl::Obj("models/fisherBoat.obj","textures/fisherBoat.jpg"));

    return true;
}

bool TXTParser::loadMap(int _map, Sea &_sea, std::vector<Object*> &_objects, SourceStore &_sourceStore)
{

    std::ifstream mapFile;
    std::ostringstream path;
    path << s_mapsPath << "map" << _map;

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
        if (!loadBehaviour(_currentParameter, behaviour, fisherBoat))
            return false;

        if (!loadBehaviourParameters(behaviour))
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

bool TXTParser::loadBehaviour(tokenizer::iterator _currentParameter, Behaviour *&_behaviour, Object *_object)
{
    try
    {
        std::string behaviourName = boost::lexical_cast<std::string>(*++_currentParameter);

        if (behaviourName == "Floating")
        {
            _behaviour = new Floating();
            _object->setRotation(ngl::Vec4(0,rand()%360,0,1));
        }
        else if (behaviourName == "Horizontal")
        {
            _behaviour = new Horizontal();
        }
        else if (behaviourName == "Vertical")
        {
            _behaviour = new Vertical();
            _object->setRotation(ngl::Vec4(0,-90,0));
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

bool TXTParser::loadBehaviourParameters(Behaviour *_behaviour)
{

    std::ifstream configFile;
    std::ostringstream path;
    path << s_behaviourParametersPath << "behaviour.conf";

    std::cout << "TXTParser: Loading behaviour configuration from " << path.str() << " ..." << std::endl;
    configFile.open(path.str().c_str(),std::ifstream::in);

    if (!configFile.is_open())
        {
            std::cout << "TXTPARSER ERROR: config file " << configFile << " not found" << std::endl;
            return false;
        }

    std::string lineBuffer;
    boost::char_separator<char> sep(" ");
    tokenizer::iterator currentToken;
    float p;

    int lineNumber = 1;

    while(!configFile.eof())
    {
        std::getline(configFile,lineBuffer,'\n');
        if (lineBuffer.size() != 0)
        {
            tokenizer tokens(lineBuffer, sep);
            currentToken = tokens.begin();

            if (*currentToken == "floatingAmplitude")
            {
                p = boost::lexical_cast<float>(*++currentToken);
                _behaviour->setFloatingAmplitude(p);
                std::cout <<"TXTParser: in line " << lineNumber << ": floatingAmplitude loaded" << std::endl;
            }
            else if (*currentToken == "floatingFrequency")
            {
                p = boost::lexical_cast<float>(*++currentToken);
                _behaviour->setFloatingFrequency(p);
                std::cout <<"TXTParser: in line " << lineNumber << ": floatingFrequency loaded" << std::endl;
            }
            else if (*currentToken == "frictionForce")
            {
                p = boost::lexical_cast<float>(*++currentToken);
                _behaviour->setFrictionForce(p);
                std::cout <<"TXTParser: in line " << lineNumber << ": frictionForce loaded" << std::endl;
            }
            else if (*currentToken == "regularSpeed")
            {
                p = boost::lexical_cast<float>(*++currentToken);
                _behaviour->setRegularSpeed(p);
                std::cout <<"TXTParser: in line " << lineNumber << ": regularSpeed loaded" << std::endl;
            }
            else if (*currentToken == "motorForce")
            {
                p = boost::lexical_cast<float>(*++currentToken);
                _behaviour->setMotorForce(p);
                std::cout <<"TXTParser: in line " << lineNumber << ": motorForce loaded" << std::endl;
            }
            else if (*currentToken == "angularVelocity")
            {
                p = boost::lexical_cast<float>(*++currentToken);
                _behaviour->setAngularVelocity(p);
                std::cout <<"TXTParser: in line " << lineNumber << ": angularVelocity loaded" << std::endl;
            }
            else if (*currentToken == "maxCamber")
            {
                p = boost::lexical_cast<float>(*++currentToken);
                _behaviour->setMaxCamber(p);
                std::cout <<"TXTParser: in line " << lineNumber << ": maxCamber loaded" << std::endl;
            }
            else
            {
                std::cout << "TXTParser: loadBehaviourParameters: in line " << lineNumber << ": WARNING: Unknown parameter" << std::endl;
            }
        }
    ++lineNumber;
    }
    return true;
}

bool TXTParser::loadPlayerControlsParameters(PlayerControls *_playerControls)
{

    //load basic behaviour parameters
    loadBehaviourParameters(_playerControls);

    std::ifstream configFile;
    std::ostringstream path;
    path << s_behaviourParametersPath << "playerControls.conf";

    std::cout << "TXTParser: Loading behaviour configuration from " << path.str() << " ..." << std::endl;
    configFile.open(path.str().c_str(),std::ifstream::in);

    if (!configFile.is_open())
        {
            std::cout << "TXTPARSER ERROR: config file " << configFile << " not found" << std::endl;
            return false;
        }

    std::string lineBuffer;
    boost::char_separator<char> sep(" ");
    tokenizer::iterator currentToken;
    float p;

    int lineNumber = 1;

    while(!configFile.eof())
    {
        std::getline(configFile,lineBuffer,'\n');
        if (lineBuffer.size() != 0)
        {
            tokenizer tokens(lineBuffer, sep);
            currentToken = tokens.begin();

            if (*currentToken == "highSpeedX")
            {
                p = boost::lexical_cast<float>(*++currentToken);
                _playerControls->setHighSpeedX(p);
                std::cout <<"TXTParser: in line " << lineNumber << ": highSpeedX loaded" << std::endl;
            }
            else if (*currentToken == "highSpeedZ")
            {
                p = boost::lexical_cast<float>(*++currentToken);
                _playerControls->setHighSpeedZ(p);
                std::cout <<"TXTParser: in line " << lineNumber << ": highSpeedZ loaded" << std::endl;
            }
            else if (*currentToken == "emersionHeight")
            {
                p = boost::lexical_cast<float>(*++currentToken);
                _playerControls->setEmersionHeight(p);
                std::cout <<"TXTParser: in line " << lineNumber << ": emersionHeight loaded" << std::endl;
            }
            else if (*currentToken == "lateralStreamForce")
            {
                p = boost::lexical_cast<float>(*++currentToken);
                _playerControls->setLateralStreamForce(p);
                std::cout <<"TXTParser: in line " << lineNumber << ": lateralStreamForce loaded" << std::endl;
            }
            else if (*currentToken == "bouncingAmplitude")
            {
                p = boost::lexical_cast<float>(*++currentToken);
                _playerControls->setBouncingAmplitude(p);
                std::cout <<"TXTParser: in line " << lineNumber << ": bouncingAmplitude loaded" << std::endl;
            }
            else if (*currentToken == "bouncingFrequency")
            {
                p = boost::lexical_cast<float>(*++currentToken);
                _playerControls->setBouncingFrequency(p);
                std::cout <<"TXTParser: in line " << lineNumber << ": bouncingFrequency loaded" << std::endl;
            }
            else
            {
                std::cout << "TXTParser: loadPlayerControlParameters: in line " << lineNumber << ": WARNING: Unknown parameter" << std::endl;
            }
        }
    ++lineNumber;
    }
    return true;
}

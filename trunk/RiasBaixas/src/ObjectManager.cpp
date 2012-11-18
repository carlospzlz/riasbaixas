#include "ObjectManager.h"

#include "SpeedBoat.h"
#include "MusselFarm.h"

/*
bool ObjectManager::loadLevel(int _level, Renderer _render)
{
    typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

    std::ifstream levelFile;
    std::ostringstream path;
    path << WORLDMANAGER_PATH << _level;
    levelFile.open(path.str().c_str(),std::ifstream::in);

    if (!levelFile.is_open())
    {
        std::cout << "ERROR: File " << levelFile << " not found" << std::endl;
        return false;
    }

    std::string lineBuffer;
    boost::char_separator<char> sep(" ");
    tokenizer::iterator currentToken;

    while(!levelFile.eof())
    {
        std::getline(levelFile,lineBuffer,'\n');
        if (lineBuffer.size() != 0)
        {
            tokenizer tokens(lineBuffer, sep);
            currentToken = tokens.begin();

            if (*currentToken == "Sea")
                loadSea(currentToken);
            else if (*currentToken == "MusselFarm")
                loadMusselFarm(currentToken);
            else if (*currentToken == "FisherBoat")
                loadFisherBoat(currentToken);
            else
                std::cout << "Unknown SeaElement" << std::endl;
        }
    }
    return false;
}
*/

void ObjectManager::addStaticObject(StaticObject *_so)
{
    m_staticObjects.push_back(_so);
    m_objects.push_back(_so);
}

void ObjectManager::addDynamicObject(DynamicObject *_do)
{
    m_dynamicObjects.push_back(_do);
    m_objects.push_back(_do);
}

void ObjectManager::createTestLevel()
{
    addStaticObject(new MusselFarm(ngl::Vec3(-2,0,0),0));
    addStaticObject(new MusselFarm(ngl::Vec3(2,0,0),0));
}

void ObjectManager::moveObjects()
{
    std::vector<DynamicObject*>::iterator lastDO = m_dynamicObjects.end();
    for(std::vector<DynamicObject*>::iterator currentDO=m_dynamicObjects.begin(); currentDO!=lastDO; ++currentDO)
    {
        (*currentDO)->move();
    }
}

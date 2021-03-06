#include "GamePlay.h"

GameState *GamePlay::run(Renderer &_renderer)
{

    static const int s_maximumFPS = 30;

    //NEEDED OBJECTS
    SourceStore mySourceStore;
    Sea mySea;
    std::vector<Object*> myObjects;
    CameraSet myCameraSet;
    playerOptions myPlayerOptions;
    Utilities myUtilities;

    myUtilities.initPlayerOptions(myPlayerOptions);

    //LOADING SOURCES AND MAP
    Parser *myParser = new TXTParser();
    myParser->loadSources(mySourceStore);
    myParser->loadMap(0, mySea, myObjects, mySourceStore);

    //LOADING THE MAIN CHARACTER: THE SPEEDBOAT
    Object* mySpeedBoat = new SpeedBoat();
    PlayerControls* myPlayerControls = new PlayerControls();
    myParser->loadPlayerControlsParameters(myPlayerControls);
    mySpeedBoat->setBehaviour(myPlayerControls);
    mySpeedBoat->setMesh(mySourceStore.getMesh("speedboat"));
    myObjects.push_back(mySpeedBoat);

    //LOADING THE NEMESIS: THE POLICEBOAT
    PoliceBoat* myPoliceBoat1 = new PoliceBoat();
    myPoliceBoat1->setType(ot_policeBoat);
    myPoliceBoat1->setPosition(ngl::Vec4(-4,0.3,-375));
    Behaviour* myFloating1 = new Floating();
    myParser->loadBehaviourParameters(myFloating1);
    myPoliceBoat1->setBehaviour(myFloating1);
    myPoliceBoat1->setMesh(mySourceStore.getMesh("policeboat"));
    myPoliceBoat1->setSpeedBoat(mySpeedBoat);
    myObjects.push_back(myPoliceBoat1);

    //LOADING TWO MORE POLICEBOATS
    PoliceBoat* myPoliceBoat2 = new PoliceBoat();
    myPoliceBoat2->setType(ot_policeBoat);
    myPoliceBoat2->setPosition(ngl::Vec4(6,0.3,-825));
    Behaviour* myFloating2 = new Floating();
    myParser->loadBehaviourParameters(myFloating2);
    myPoliceBoat2->setBehaviour(myFloating2);
    myPoliceBoat2->setMesh(mySourceStore.getMesh("policeboat"));
    myPoliceBoat2->setSpeedBoat(mySpeedBoat);
    myObjects.push_back(myPoliceBoat2);

    PoliceBoat* myPoliceBoat3 = new PoliceBoat();
    myPoliceBoat3->setType(ot_policeBoat);
    myPoliceBoat3->setPosition(ngl::Vec4(-6,0.3,-950));
    Behaviour* myFloating3 = new Floating();
    myParser->loadBehaviourParameters(myFloating3);
    myPoliceBoat3->setBehaviour(myFloating3);
    myPoliceBoat3->setMesh(mySourceStore.getMesh("policeboat"));
    myPoliceBoat3->setSpeedBoat(mySpeedBoat);
    myObjects.push_back(myPoliceBoat3);


    //LOADING AND LINKING CAMERAS
    myCameraSet.loadCameras(_renderer.getWindowWidth(),_renderer.getWindowHeight());
    myCameraSet.setTarget(mySpeedBoat);

    //PHYSICS ENGINE
    PhysicsEngine *myPhysicsEngine = new BSpherePE();

    //TIMING
    Uint32 startingTick;
    int frameCounter = 0;
    Uint32 lastStartingSecond = SDL_GetTicks();
    int currentFPS = 0;

    //GAME LOOP
    while (myPlayerOptions.running && !myPlayerOptions.changeState)
    {
        startingTick = SDL_GetTicks();

        myUtilities.readPlayerInput(*myPlayerControls, myPlayerOptions, _renderer.isFullScreen());

        myUtilities.setWindow(_renderer,myPlayerOptions);
        myUtilities.setCamera(myCameraSet, _renderer, myPlayerOptions);

        if (!myPlayerOptions.pause)
        {
            checkActiveObjects(myObjects,myCameraSet.getCurrentCamera());
            updateObjects(myObjects);
            checkCollisions(myObjects, mySea, myPhysicsEngine);
            //mySpeedBoat->info();
            //myPoliceBoat1->info();

            myCameraSet.updateCameras();

            _renderer.render(mySea,myObjects,*myCameraSet.getCurrentCamera(),myPlayerOptions.debugMode);
        }

        myUtilities.regulateFPS(startingTick, frameCounter, lastStartingSecond, currentFPS, s_maximumFPS);

        std::cout << "WORKING AT "<< currentFPS <<" FPS" << std::endl;

        //std::cout << "GAMEMANAGER: DISTANCE TO THE BEACH: " << (SEA_DEPTH+mySpeedBoat.getPosition().m_z) << std::endl;

        //std::cin.ignore();
    }

    releaseMemory(myObjects);

    if (!myPlayerOptions.running)
        return NULL;

    _renderer.fadeOut();
    return (new GameMenu());
}

void GamePlay::checkActiveObjects(std::vector<Object*> &_objects, ngl::Camera *_cam)
{
    float currentZ = _cam->getEye().m_z;
    float far = _cam->getFar();

    std::vector<Object*>::iterator lastO = _objects.end();
    for(std::vector<Object*>::iterator currentO=_objects.begin(); currentO!=lastO; ++currentO)
    {
        (*currentO)->checkActive(currentZ, far);
    }
}

void GamePlay::updateObjects(std::vector<Object*> &_objects)
{
    std::vector<Object*>::iterator endO = _objects.end();
    for(std::vector<Object*>::iterator currentO=_objects.begin(); currentO!=endO;++currentO)
    {
        if ((*currentO)->isActive())
            (*currentO)->update();
    }
}

void GamePlay::checkCollisions(std::vector<Object*> &_objects, const Sea &_sea, PhysicsEngine *_physicsEngine)
{

    clearCollisionInformation(_objects);

    std::vector<Object*>::iterator endO = _objects.end();
    std::vector<Object*>::iterator lastO = endO-1;

    for(std::vector<Object*>::iterator o1=_objects.begin(); o1!=lastO; ++o1)
    {
        if ((*o1)->isActive())
        {
            for(std::vector<Object*>::iterator o2=o1+1; o2!= endO; ++o2)
            {
                if ((*o2)->isActive())
                {
                    _physicsEngine->checkCollision(*o1,*o2);
                }
            }
        }
    }

    checkCollisionsWithSeaLimits(_objects, _sea);
}

void GamePlay::clearCollisionInformation(std::vector<Object*> &_objects)
{
    std::vector<Object*>::iterator endO = _objects.end();
    for(std::vector<Object*>::iterator currentO=_objects.begin(); currentO!=endO; ++currentO)
    {
        if ((*currentO)->isActive())
        {
            (*currentO)->setCollided(false);
            (*currentO)->getDOF().up = true;
            (*currentO)->getDOF().down = true;
            (*currentO)->getDOF().left = true;
            (*currentO)->getDOF().right = true;
            (*currentO)->getDOF().forward = true;
            (*currentO)->getDOF().backward = true;
        }
    }
}

void GamePlay::checkCollisionsWithSeaLimits(std::vector<Object*> &_objects, const Sea &_sea)
{
    std::vector<Object*>::iterator lastO = _objects.end();
    for(std::vector<Object*>::iterator currentO=_objects.begin(); currentO!=lastO; ++currentO)
    {
        if ((*currentO)->isActive())
        {
            if ((*currentO)->getPosition().m_x<-_sea.getWidth()/2.0)
            {
                (*currentO)->getDOF().left = false;
                (*currentO)->setCollided(true);
            }

            if ((*currentO)->getPosition().m_x>_sea.getWidth()/2.0)
            {
                (*currentO)->getDOF().right = false;
                (*currentO)->setCollided(true);
            }
        }
    }
}

void GamePlay::releaseMemory(std::vector<Object*> &_objects)
{
    std::cout << "Game: deleting objects and behaviours ..." << std::endl;

    std::vector<Object*>::iterator lastO = _objects.end();
    for(std::vector<Object*>::iterator currentO=_objects.begin(); currentO!=lastO; ++currentO)
    {
        delete *currentO;
    }
}

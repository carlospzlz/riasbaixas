#include <vector>
#include <string>
#include <ngl/Obj.h>
#include <cassert>
#include "include/Models.h"


Models::~Models()
{
    std::vector<ngl::Obj*>::iterator firstMesh = m_models.begin();
    std::vector<ngl::Obj*>::iterator lastMesh = m_models.end();

    std::vector<ngl::Obj*>::iterator currentMesh = firstMesh;

    while (currentMesh != lastMesh)
    {
        std::cout << "Deleting " << getModelName(currentMesh-firstMesh) << " model" << std::endl;
        delete *currentMesh;
    }
}

std::string Models::getModelName(const int _index)
{
    assert(_index>=0 && _index<N_MODELS);
    switch (_index)
    {
    case SPEEDBOAT:
        return "Speedboat";
    }
    return "unknown model name";
}

void Models::addModel(const int _index, const std::string _modelPath)
{
    assert(_index>=0 && _index<N_MODELS);
    ngl::Obj *model = new ngl::Obj(_modelPath);
    model->createVAO();
    //model->calcBoundingSphere();
    model->draw();
    //m_models[_index] = model;
    std::cout << getModelName(_index) << " model loaded" << std::endl;
}

void Models::draw(const int _index)
{
    assert(_index>=0 && _index<N_MODELS);
    m_models[_index]->draw();
}


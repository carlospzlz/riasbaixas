#include <vector>
#include <string>
#include <ngl/Obj.h>
#include <cassert>
#include "include/Models.h"


Models::Models()
{
    m_models.resize(N_MODELS);
}

Models::~Models()
{

    for(int i=0; i<m_models.size(); ++i)
    {
        std::cout << "Deleting " << getModelName(i) << " model" << std::endl;
        delete m_models[i];
    }    
}

std::string Models::getModelName(const int _index)
{
    assert(_index>=0 && _index<N_MODELS);
    switch (_index)
    {
    case SPEEDBOAT:
        return "speedboat";
    }
    return "unknown";
}

void Models::addModel(const int _index, const std::string _modelPath)
{
    //models must be added in order
    assert(_index>=0 && _index<N_MODELS);
    ngl::Obj *model = new ngl::Obj(_modelPath);
    model->createVAO();
    model->calcBoundingSphere();
    m_models[_index] = model;
    std::cout << getModelName(_index) << " model loaded" << std::endl;
}

ngl::Obj *Models::getModel(const int _index)
{
    return m_models[_index];
}

void Models::draw(const int _index)
{
    assert(_index>=0 && _index<N_MODELS);
    m_models[_index]->draw();
}

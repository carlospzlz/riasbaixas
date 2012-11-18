#include <vector>
#include <string>
#include <ngl/Obj.h>
#include <cassert>
#include "SourceManager.h"

SourceManager::~SourceManager()
{

    std::map<std::string,ngl::Obj*>::iterator lastMesh = m_meshes.end();
    for (std::map<std::string,ngl::Obj*>::iterator currentMesh = m_meshes.begin(); currentMesh!=lastMesh; ++currentMesh)
    {
        std::cout << "Deleting mesh " << currentMesh->first << std::endl;
        delete currentMesh->second;
    }

}

void SourceManager::addMesh(const std::string _key, ngl::Obj* _mesh)
{
    std::cout << "Loading mesh " << _key << std::endl;
    _mesh->createVAO();
    _mesh->calcBoundingSphere();
    m_meshes[_key] = _mesh;
}

ngl::Obj* SourceManager::getMesh(const std::string _key)
{
    return m_meshes[_key];
}

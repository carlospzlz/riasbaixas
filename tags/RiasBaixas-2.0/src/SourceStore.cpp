#include <vector>
#include <string>
#include <ngl/Obj.h>
#include <cassert>
#include "SourceStore.h"

SourceStore::~SourceStore()
{
    std::cout << "SourceStore: deleting meshes ..." << std::endl;
    std::map<std::string,ngl::Obj*>::iterator lastMesh = m_meshes.end();
    for (std::map<std::string,ngl::Obj*>::iterator currentMesh = m_meshes.begin(); currentMesh!=lastMesh; ++currentMesh)
    {
        delete currentMesh->second;
    }

}

void SourceStore::addMesh(const std::string _key, ngl::Obj* _mesh)
{
    std::cout << "SourceStore: Loading mesh " << _key << std::endl;
    _mesh->createVAO();
    _mesh->calcBoundingSphere();
    m_meshes[_key] = _mesh;
}

ngl::Obj *SourceStore::getMesh(const std::string _key)
{
    if (m_meshes.find(_key)!=m_meshes.end())
        return m_meshes[_key];
    else
    {
        return NULL;
        std::cout << "SourceStore: WARNING: Mesh " << _key << " not found!" << std::endl;
    }
}

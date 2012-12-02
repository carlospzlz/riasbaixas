#ifndef SOURCEMANAGER_H
#define SOURCEMANAGER_H

#include <map>
#include <string>
#include <ngl/Obj.h>


class SourceManager
{

private:
    std::map<std::string,ngl::Obj*> m_meshes;

public:
    ~SourceManager();
    void addMesh(const std::string _key, ngl::Obj* _mesh);
    ngl::Obj *getMesh(const std::string _key);

};


#endif // SOURCEMANAGER_H

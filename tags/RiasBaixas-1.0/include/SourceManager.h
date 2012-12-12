#ifndef SOURCEMANAGER_H
#define SOURCEMANAGER_H

/**
 * @file SourceManager
 * @brief this class stores all the sources needed for the game, such
 * as meshes, textures, images, sounds, etc.
 */
#include <map>
#include <string>
#include <ngl/Obj.h>


/**
 * @class SourceManager
 * @brief this class stores all the sources needed for the game, such
 * as meshes, textures, images, sounds, etc.
 */
class SourceManager
{

private:
    /**
     * @brief all the meshes within the textures
     */
    std::map<std::string,ngl::Obj*> m_meshes;

public:
    ~SourceManager();
    void addMesh(const std::string _key, ngl::Obj* _mesh);
    ngl::Obj *getMesh(const std::string _key);

};


#endif // SOURCEMANAGER_H

#ifndef SOURCESTORE_H
#define SOURCESTORE_H

/**
 * @file SourceStore
 * @brief this class stores all the sources needed for the game, such
 * as meshes, textures, images, sounds, etc.
 */
#include <map>
#include <string>
#include <ngl/Obj.h>


/**
 * @class SourceStore
 * @brief this class stores all the sources needed for the game, such
 * as meshes, textures, images, sounds, etc.
 */
class SourceStore
{

private:
    /**
     * @brief all the meshes within the textures
     */
    std::map<std::string,ngl::Obj*> m_meshes;

public:
    ~SourceStore();
    void addMesh(const std::string _key, ngl::Obj* _mesh);
    ngl::Obj *getMesh(const std::string _key);

};


#endif // SOURCESTORE_H

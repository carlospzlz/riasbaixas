#include "StaticObject.h"

StaticObject::StaticObject(objectType _type, ngl::Obj *_mesh, std::string _primName, ngl::Vec3 _pos, ngl::Vec4 _rot, ngl::Vec4 _sca, int _dam)
    : Object(_type, _mesh, _primName, _pos, _rot, _sca, _dam)
{
    std::cout << "SO created : ";
}

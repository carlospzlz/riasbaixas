#ifndef STATICOBJECT_H
#define STATICOBJECT_H

#include <ngl/Obj.h>
#include <ngl/Vec3.h>
#include <string>

#include "Object.h"

class StaticObject : public Object
{

protected:
    StaticObject(objectType _type, ngl::Obj *_mesh, std::string _primName, ngl::Vec3 _pos, ngl::Vec4 _rot, ngl::Vec4 _sca, int _dam);

public:

};

#endif // STATICOBJECT_H

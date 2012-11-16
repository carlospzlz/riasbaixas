#ifndef STATICSEAELEMENT_H
#define STATICSEAELEMENT_H

#include <ngl/Obj.h>
#include <ngl/Vec3.h>
#include <string>

#include "SeaElement.h"

class StaticSeaElement : public SeaElement
{

protected:
    StaticSeaElement(SeaElementType _type, ngl::Obj *_model, std::string _primName, ngl::Vec3 _pos, ngl::Vec4 _rot, ngl::Vec4 _sca);

public:

};

#endif // STATICSEAELEMENT_H

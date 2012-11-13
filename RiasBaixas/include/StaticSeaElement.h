#ifndef STATICSEAELEMENT_H
#define STATICSEAELEMENT_H

#include <ngl/Obj.h>
#include <ngl/Vec3.h>
#include <string>

#include "SeaElement.h"
#include "DynamicSeaElement.h"

class StaticSeaElement : public SeaElement
{

protected:
    StaticSeaElement(ngl::Obj *_model, std::string _primName, ngl::Vec3 _pos, ngl::Vec4 _rot, ngl::Vec4 _sca);

public:
    void interactsWith(DynamicSeaElement _dse);
    void info();

};

#endif // STATICSEAELEMENT_H

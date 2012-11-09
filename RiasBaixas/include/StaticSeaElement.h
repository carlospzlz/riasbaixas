#ifndef STATICSEAELEMENT_H
#define STATICSEAELEMENT_H

#include <ngl/Obj.h>
#include <ngl/Vec3.h>
#include <string>
#include "SpeedBoat.h"

class StaticSeaElement
{

private:
    ngl::Obj *m_model;
    ngl::Vec3 m_position;
    std::string m_primForDebugging;

protected:
    StaticSeaElement(ngl::Obj *_model, std::string _prim, ngl::Vec3 _pos);

public:
    void draw(bool _debuggingMode);
};

#endif // STATICSEAELEMENT_H

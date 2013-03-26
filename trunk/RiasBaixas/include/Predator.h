#ifndef PREDATOR_H
#define PREDATOR_H

#include "Behaviour.h"
#include "PlayerControls.h"
#include "Object.h"
#include "TXTParser.h"

class Predator : public Behaviour
{

private:
    Object *m_prey;
    PlayerControls *m_controls;

public:
    Predator();
    void setPrey(Object* _p) { m_prey = _p; }
    virtual std::string getName() { return "Predator"; }
    virtual void move(ngl::Transformation &_transform, ngl::Vec4 &_velocity, ngl::Vec4 &_angularVelocity, degreesOfFreedom &_dof);
};

#endif // PREDATOR_H

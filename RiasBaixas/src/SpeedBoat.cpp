#include "SpeedBoat.h"
#include <iostream>

SpeedBoat::SpeedBoat(ngl::Obj *_model)
{
    m_model = _model;
    m_position = ngl::Vec3(0,0,0);
    m_rotation = ngl::Vec3(0,0,0);
    m_load = MAX_LOAD;
    std::cout << "SpeedBoat created and ready to rock" << std::endl;
}

void SpeedBoat::draw()
{
    m_model->draw();
}


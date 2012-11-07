#include "SpeedBoat.h"
#include <iostream>

SpeedBoat::SpeedBoat(ngl::Obj *_model)
{
    m_model = _model;
    m_position = ngl::Vec3(0,0,0);
    m_rotation = ngl::Vec4(0,-90,0,0);
    m_load = MAX_LOAD;
    std::cout << "SpeedBoat created and ready to rock" << std::endl;
}

void SpeedBoat::draw(const std::string &_shader, ngl::Camera *_cam)
{   
    ngl::ShaderLib *shader = ngl::ShaderLib::instance();
    (*shader)[_shader]->use();

    m_transform.setPosition(m_position);
    m_transform.setRotation(m_rotation);

    ngl::Material m(ngl::GOLD);
    m.loadToShader("material");

    ngl::Mat4 MVP=m_transform.getMatrix()*_cam->getVPMatrix();

    shader->setShaderParamFromMat4("MVP",MVP);
    m_model->draw();
    //ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
    //prim->draw("teapot");

}

void SpeedBoat::moveRight()
{
    m_position.m_x += .1;
    //m_rotation.m_x += 3;
    m_rotation.m_z += 3;
    //m_rotation.m_z += -2;
    //m_rotation.m_z += 2;
    //m_position.m_z += .1;
}

void SpeedBoat::moveLeft()
{
    m_position.m_x -= .1;
    //m_rotation.m_x -= 3;
    m_rotation.m_z -= 3;
    //m_rotation.m_z += 2;
    //m_rotation.m_z += -2;

}


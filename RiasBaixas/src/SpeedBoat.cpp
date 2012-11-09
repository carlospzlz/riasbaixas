#include "SpeedBoat.h"
#include <iostream>
#include <SDL/SDL.h>
#include <math.h>

SpeedBoat::SpeedBoat(ngl::Obj *_model)
{
    m_model = _model;
    m_position = ngl::Vec3(0,0,0);
    m_rotation = ngl::Vec4(0,90,0,0);
    m_load = MAX_LOAD;
    std::cout << "SpeedBoat created and ready to rock" << std::endl;
}

void SpeedBoat::draw(const std::string &_shader, ngl::Camera *_cam)
{   
    ngl::ShaderLib *shader = ngl::ShaderLib::instance();
    (*shader)[_shader]->use();

    m_transform.setPosition(m_position);
    m_transform.setRotation(m_rotation);

    //ngl::Material m(ngl::GOLD);
    //m.loadToShader("material");

    ngl::Mat4 MVP=m_transform.getMatrix()*_cam->getVPMatrix();

    shader->setShaderParamFromMat4("MVP",MVP);
    //m_model->draw();
    ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
    prim->draw("teapot");

}

void SpeedBoat::moveRight()
{
    m_rotation.m_y -= 1;
    m_rotation.m_x += 1;
    m_position.m_x += 0.1;
}

void SpeedBoat::moveLeft()
{
    m_rotation.m_y += 1;
    m_rotation.m_x -= 1;
    m_position.m_x -= 0.1;
}

void SpeedBoat::moveUp()
{
    m_rotation.m_x -= 1;
}


void SpeedBoat::moveDown()
{
    m_rotation.m_x += 1;
}

void SpeedBoat::rotateInX()
{
    m_rotation.m_x +=0.8;
}

void SpeedBoat::rotateInY()
{
    m_rotation.m_y +=0.8;
}

void SpeedBoat::rotateInZ()
{
    m_rotation.m_z +=0.8;
}

void SpeedBoat::floating()
{
    m_position.m_y = 0.1*std::sin(M_PI/150*ticks);
    ++ticks;
}

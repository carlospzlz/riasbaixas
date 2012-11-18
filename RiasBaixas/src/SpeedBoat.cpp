#include "SpeedBoat.h"
#include <iostream>
#include <SDL/SDL.h>
#include <math.h>

SpeedBoat::SpeedBoat(Controller *_controller, ngl::Obj *_mesh, int _dam) :
    DynamicObject(ot_speedBoat, _mesh, "teapot", ngl::Vec3(0,0,0), ngl::Vec4(0,90,0,1), ngl::Vec4(1,1,1,1),
                  _dam, ngl::Vec3(SPEEDBOAT_SPEED,0,SPEEDBOAT_SPEED), _controller)
{
    m_load = MAX_LOAD;
    std::cout << "SpeedBoat created and ready to rock." << std::endl;
}

SpeedBoat::SpeedBoat(Controller *_controller, int _dam) :
    DynamicObject(ot_speedBoat, NULL, "teapot", ngl::Vec3(0,0,0), ngl::Vec4(0,90,0,1), ngl::Vec4(1,1,1,1),
                  _dam, ngl::Vec3(SPEEDBOAT_SPEED,0,SPEEDBOAT_SPEED), _controller)
{
    m_load = MAX_LOAD;
    std::cout << "SpeedBoat created and ready to rock." << std::endl;
}

/*
void SpeedBoat::draw(const std::string &_shader, ngl::Camera &_cam, int _debugMode)
{   
    ngl::ShaderLib *shader = ngl::ShaderLib::instance();
    (*shader)[_shader]->use();

    m_transform.setPosition(m_position);
    m_transform.setRotation(m_rotation);
    m_transform.setScale(m_scale);

    //ngl::Material m(ngl::GOLD);
    //m.loadToShader("material");

    ngl::Mat4 MVP=m_transform.getMatrix()*_cam.getVPMatrix();

    shader->setShaderParamFromMat4("MVP",MVP);

    switch (_debugMode)
    {
    case 1:
        ngl::VAOPrimitives::instance()->draw("teapot");
        break;
    case 2:
        m_model->drawBBox();
        break;
    default:
        m_model->draw();
    }

}*/

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

void SpeedBoat::move()
{
    std::cout << "SpeedBoat moving!" << std::endl;
    m_controller->move(m_position, m_rotation, m_velocity, SPEEDBOAT_SPEED_FACTOR, SPEEDBOAT_COMBER_STEP, SPEEDBOAT_COMBER_MAX);
}

/*
void SpeedBoat::info()
{
    std::cout << "this is a SpeedBoat" << std::endl;
}*/

#include "Diagonal.h"
#include "Sea.h"

void Diagonal::move(ngl::Vec3 &_pos, ngl::Vec4 &_rot, ngl::Vec3 &_vel, const int _factorSpeed, const int _combStep, const int _maxComb)
{
    //Diagonal cuadrant

    if (_pos.m_x<(-SEA_WIDTH/2))
    {
        if (_vel.m_z>0)
            --_vel.m_z;
        else
            ++_vel.m_z;
        ++_vel.m_x;
    }
    else if (_pos.m_x>(SEA_WIDTH/2))
    {
        if (_vel.m_z>0)
            --_vel.m_z;
        else
            ++_vel.m_z;
        --_vel.m_x;
    }
    else
    {
        if (std::abs(_vel.m_z)>std::abs(_vel.m_x))
        {
            --_vel.m_z;
            ++_vel.m_x;
        }

        if (std::abs(_vel.m_z)<std::abs(_vel.m_x))
        {
            ++_vel.m_z;
            --_vel.m_x;
        }
    }

    _pos = _pos + _vel;

    std::cout<<"VELOCITY VECTOR"<<_vel<<std::endl;

}

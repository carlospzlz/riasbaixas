#include <PlayerControls.h>

void PlayerControls::setLeft(bool _pressed)
{
    if (_pressed)
        m_left = true;
    else
        m_left = false;
}

void PlayerControls::setRight(bool _pressed)
{
    if (_pressed)
        m_right = true;
    else
        m_right = false;
}

void PlayerControls::setSpeedUp(bool _pressed)
{
    if (_pressed)
        m_speedUp = true;
    else
        m_speedUp = false;
    std::cout << "SPEED UP!!" << std::endl;
}

void PlayerControls::move(ngl::Vec3 &_pos, ngl::Vec4 &_rot, const ngl::Vec4 &_velocity)
{
    if (m_speedUp)
        _pos.m_z += 2*_velocity.m_z;
    else
        _pos.m_z += _velocity.m_z;

    if (m_left && !m_right)
    {
        //comber left
        _pos.m_x -= _velocity.m_x;
        _rot.m_y += 1;
        _rot.m_x -= 1;
    }

    if (m_right && !m_left)
    {
        //comber right
        _pos.m_x += _velocity.m_x;
        _rot.m_y -= 1;
        _rot.m_x += 1;
    }

    if (!m_left && !m_right)
    {
        //recover comber anti-right
        if (_rot.m_y<0) _rot.m_y += 1;
        if (_rot.m_x>0) _rot.m_x -= 1;
        //recover comber anti-left
        if (_rot.m_y>0) _rot.m_y -= 1;
        if (_rot.m_x<0) _rot.m_x += 1;
    }

    //floating effect
    _pos.m_y = AMPLITUDE*sin(FRECUENCY*m_ticks);

}

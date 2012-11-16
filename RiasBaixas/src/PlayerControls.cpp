#include <PlayerControls.h>

PlayerControls::PlayerControls()
{
    m_left = false;
    m_right = false;
    m_speedUp = false;
    m_internalVelInZ = 0;
    m_ticksFloating = 0;
    m_ticksJumping = 0;
}

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

void PlayerControls::move(ngl::Vec3 &_pos, ngl::Vec4 &_rot, const ngl::Vec3 &_vel, const int _factorSpeed, const int _combStep, const int _maxComb)
{
    std::cout << "PlayerControls: player controlling [" << m_left << " "<< m_speedUp << " "<< m_right << "]"<< std::endl;

    if (m_internalVelInZ == 0)
        m_internalVelInZ = _vel.m_z;

    //turning and combering
    if (m_left && !m_right)
    {
        //comber left
        _pos.m_x -= _vel.m_x;
        _rot.m_y += _combStep;
        _rot.m_x -= _combStep;
    }

    if (m_right && !m_left)
    {
        //comber right
        _pos.m_x += _vel.m_x;
        _rot.m_y -= _combStep;
        _rot.m_x += _combStep;
    }

    //clamping
    if (_rot.m_y > (90+_maxComb))
        _rot.m_y = 90+_maxComb;
    if (_rot.m_y < (90-_maxComb))
        _rot.m_y = 90-_maxComb;
    if (_rot.m_x > _maxComb)
        _rot.m_x = _maxComb;
    if (_rot.m_x < -_maxComb)
        _rot.m_x = -_maxComb;


    //recover comber
    if (!m_left && !m_right)
    {
        //recover comber anti-right
        if (_rot.m_y<90) _rot.m_y += _combStep;
        if (_rot.m_x>0) _rot.m_x -= _combStep;
        //recover comber anti-left
        if (_rot.m_y>90) _rot.m_y -= _combStep;
        if (_rot.m_x<0) _rot.m_x += _combStep;
    }

    //FLOATING AND JUMPING EFFECT

    //recalculating high ont the water and speed
    if (m_speedUp && m_internalVelInZ<_factorSpeed*_vel.m_z)
    {
        _pos.m_y += 0.01;
        m_internalVelInZ += 0.005;
        m_ticksJumping = 0;
    }

    if (!m_speedUp && m_internalVelInZ>_vel.m_z)
    {
        _pos.m_y -= 0.01;
        m_internalVelInZ -= 0.005;
        m_ticksFloating = 0;
    }

    //updating positions
     _pos.m_z -= m_internalVelInZ;

     if (m_internalVelInZ >= _vel.m_z)
         _pos.m_y = _pos.m_y + PLAYERCONTROLS_AMPLITUDE*std::cos(PLAYERCONTROLS_FRECUENCY*m_ticksFloating);

     if (m_internalVelInZ <= _factorSpeed*_vel.m_z)
         _pos.m_y = _pos.m_y + std::abs(PLAYERCONTROLS_AMPLITUDE*std::cos(PLAYERCONTROLS_FRECUENCY*m_ticksJumping));

     ++m_ticksFloating;
     ++m_ticksJumping;

     std::cout << _pos.m_y << " \t" << m_internalVelInZ << std::endl;

    /*
    if (m_speedUp)

    else
    {
        _pos.m_y -= 0.001;
        m_internalVelInZ -= 0.01;
    }

     std::cout << "PLAYERCONTROLS" << m_internalVelInZ << m_amplitude << std::endl;

    //clamping
    if (_pos.m_y> _factorSpeed*PLAYERCONTROLS_AMPLITUDE)
        _pos.m_y = _factorSpeed*PLAYERCONTROLS_AMPLITUDE;
    if (_pos.m_y < 0)
        _pos.m_y = 0;
    if (m_internalVelInZ > _factorSpeed*_vel.m_z)
        m_internalVelInZ = _factorSpeed*_vel.m_z;
    if (m_internalVelInZ < _vel.m_z)
        m_internalVelInZ = _vel.m_z;

     std::cout << "PLAYERCONTROLS" << m_internalVelInZ << m_amplitude << std::endl;

    //updating position
    _pos.m_z -= m_internalVelInZ;

    //jumping and flying on the waves
    if (m_internalVelInZ == _vel.m_z)
        _pos.m_y = _pos.m_y + m_amplitude*std::cos(PLAYERCONTROLS_FRECUENCY*m_ticks);

    if (m_internalVelInZ == _factorSpeed*_vel.m_z)
        _pos.m_y = _pos.m_y + std::abs(m_amplitude*std::cos(PLAYERCONTROLS_FRECUENCY*m_ticks));

    ++m_ticks;

    std::cout << "PLAYERCONTROLS" << m_internalVelInZ << m_amplitude << std::endl;

    /*
    if (m_speedUp)
        _rot.m_z += 1;
    else
        if (_rot.m_z > 0) _rot.m_z -= 1;
        */

}

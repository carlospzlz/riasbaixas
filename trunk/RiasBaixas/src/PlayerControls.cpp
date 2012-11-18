#include <PlayerControls.h>

PlayerControls::PlayerControls()
{
    m_left = false;
    m_right = false;
    m_speedUp = false;
    m_internalVelInZ = 0;
    m_floating = true;
    m_ticksFloating = 0;
    m_ticksBouncing = 0;
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
    //std::cout << "SPEED UP!!" << std::endl;
}

void PlayerControls::move(ngl::Vec3 &_pos, ngl::Vec4 &_rot, const ngl::Vec3 &_vel, const int _factorSpeed, const int _combStep, const int _maxComb)
{
    //std::cout << "PlayerControls: player controlling [" << m_left << " "<< m_speedUp << " "<< m_right << "]"<< std::endl;

    //START IN MOVEMENT
    if (m_internalVelInZ == 0)
        m_internalVelInZ = _vel.m_z;

    //TURNING AND COMBERING
    if (m_left && !m_right)
    {
        //comber left
        if (_pos.m_x > -SEA_WIDTH/2) _pos.m_x -= _vel.m_x;
        if (_rot.m_y < 90+_maxComb) _rot.m_y += _combStep;
        if (_rot.m_x > -_maxComb) _rot.m_x -= _combStep;
    }

    if (m_right && !m_left)
    {
        //comber right
        if (_pos.m_x < SEA_WIDTH/2) _pos.m_x += _vel.m_x;
        if (_rot.m_y > 90-_maxComb) _rot.m_y -= _combStep;
        if (_rot.m_x < _maxComb) _rot.m_x += _combStep;
    }

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

    //ACCELERATING
    if (m_speedUp && m_internalVelInZ<_factorSpeed*_vel.m_z)
        m_internalVelInZ += PLAYERCONTROLS_ACELARATION_STEP;

    if (m_speedUp && _pos.m_y<PLAYERCONTROLS_EMERSION)
    {
        _pos.m_y += PLAYERCONTROLS_ACELARATION_STEP;
        m_floating = false;
    }

    if (m_speedUp && _pos.m_y>=PLAYERCONTROLS_EMERSION & !m_bouncing)
    {
        m_bouncing = true;
        m_ticksBouncing = 0;
    }

    //DECCELERATING
    if (!m_speedUp && m_internalVelInZ>_vel.m_z)
        m_internalVelInZ -= PLAYERCONTROLS_DECELARATION_STEP;

    if (!m_speedUp && _pos.m_y>0)
    {
        _pos.m_y -= PLAYERCONTROLS_DECELARATION_STEP;
        m_bouncing = false;
    }

    if (!m_speedUp && _pos.m_y<=0 && !m_floating)
    {
        m_floating = true;
        m_ticksFloating = 0;
    }

    //UPDATING POSITIONS (FLOATING AND BOUNCING EFFECT)
     _pos.m_z -= m_internalVelInZ;

     if (m_floating)
     {
         _pos.m_y = PLAYERCONTROLS_AMPLITUDE_FLOATING*std::sin(PLAYERCONTROLS_FRECUENCY*m_ticksFloating);
         ++m_ticksFloating;
     }

     if (m_bouncing)
     {
         _pos.m_y = PLAYERCONTROLS_EMERSION + std::abs(PLAYERCONTROLS_AMPLITUDE_BOUNCING*std::sin(PLAYERCONTROLS_FRECUENCY*m_ticksBouncing));
          ++m_ticksBouncing;
     }


     //std::cout << m_floating << ":" << m_ticksFloating << "\t"
     //          << m_bouncing << ":" << m_ticksBouncing << std::endl;

}

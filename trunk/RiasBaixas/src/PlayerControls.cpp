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
    m_movementForce = ngl::Vec3(0,0,0);
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

void PlayerControls::move(ngl::Vec3 &_pos, ngl::Vec4 &_rot, ngl::Vec3 &_vel, float &_maxSpeed, const bool _jumping, const degreesOfFreedom _dof)
{
    //std::cout << "PlayerControls: player controlling [" << m_left << " "<< m_speedUp << " "<< m_right << "]"<< std::endl;

    if (m_speedUp)
        _maxSpeed = PLAYERCONTROLS_HIGHSPEED;
    else
        _maxSpeed = PLAYERCONTROLS_LOWSPEED;

    if (_jumping)
        std::cout << "it jumps" << std::endl;
    else
    {

        //MOVING IN X

        if (m_left && !m_right)
        {
            //comber left
            m_movementForce.m_x -= PLAYERCONTROLS_FORCESTEP;
            _rot.m_y += PLAYERCONTROLS_CAMBER_STEP;
            _rot.m_x -= PLAYERCONTROLS_CAMBER_STEP;
        }

        if (m_right && !m_left)
        {
            //comber right
            m_movementForce.m_x += PLAYERCONTROLS_FORCESTEP;
            _rot.m_y -= PLAYERCONTROLS_CAMBER_STEP;
            _rot.m_x += PLAYERCONTROLS_CAMBER_STEP;
        }

        //recover comber
        if (!m_left && !m_right)
        {
            //recover comber anti-right
            if (_rot.m_y<90) _rot.m_y += PLAYERCONTROLS_CAMBER_STEP;
            if (_rot.m_x>0) _rot.m_x -= PLAYERCONTROLS_CAMBER_STEP;
            //recover comber anti-left
            if (_rot.m_y>90) _rot.m_y -= PLAYERCONTROLS_CAMBER_STEP;
            if (_rot.m_x<0) _rot.m_x += PLAYERCONTROLS_CAMBER_STEP;
        }

        //MOVING IN Z

        //accelerating
        m_movementForce.m_z = PLAYERCONTROLS_FORCESTEP;

        if (m_speedUp && _pos.m_y<PLAYERCONTROLS_EMERSION_HIGH && !m_bouncing)
        {
            m_floating = false;
            m_movementForce.m_y = PLAYERCONTROLS_FORCESTEP;
        }

        if (_vel.m_z == PLAYERCONTROLS_HIGHSPEED && _pos.m_y == PLAYERCONTROLS_EMERSION_HIGH && !m_bouncing)
        {
            m_bouncing = true;
            m_ticksBouncing = 0;
        }

        //bouncing
        if (m_bouncing)
        {
            _vel.m_y = PLAYERCONTROLS_EMERSION_HIGH + std::abs(PLAYERCONTROLS_AMPLITUDE_BOUNCING*std::cos(PLAYERCONTROLS_FRECUENCY*m_ticksBouncing));
             ++m_ticksBouncing;
        }

        //decelerating
        if (!m_speedUp && _pos.m_y > 0 && !m_floating)
        {
            m_bouncing = false;
            m_movementForce.m_y -= PLAYERCONTROLS_FORCESTEP;
        }

        if (_vel.m_z == PLAYERCONTROLS_LOWSPEED && _vel.m_y == 0 && !m_floating)
        {
            m_floating = true;
            m_ticksFloating = 0;
        }

        //floating
        if (m_floating)
        {
            _vel.m_y = PLAYERCONTROLS_AMPLITUDE_FLOATING*std::cos(PLAYERCONTROLS_FRECUENCY*m_ticksFloating);
            ++m_ticksFloating;
        }

        //CLAMPING
        _pos.m_x = std::max(-SEA_WIDTH/2.0, _pos.m_x);
        _pos.m_x = std::min(SEA_WIDTH/2.0, _pos.m_x);
        _rot.m_y = std::max(90-PLAYERCONTROLS_CAMBER, _rot.m_y);
        _rot.m_y = std::min(90+PLAYERCONTROLS_CAMBER, rot.m_y);
        _rot.m_x = std::max(-PLAYERCONTROLS_CAMBER, rot.m_x);
        _rot.m_x = std::max(PLAYERCONTROLS_CAMBER, rot.m_x);


    }


    _vel += m_movementForce;

    _pos += _vel;


    //ACCELERATING
   /* if (m_speedUp && m_internalVelInZ<_factorSpeed*_vel.m_z)
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
    }*/

    //DECCELERATING
   /* if (!m_speedUp && m_internalVelInZ>_vel.m_z)
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
*/
    //UPDATING POSITIONS (FLOATING AND BOUNCING EFFECT)
     /*_pos.m_z -= m_internalVelInZ;

     if (m_floating)
     {
         _pos.m_y = PLAYERCONTROLS_AMPLITUDE_FLOATING*std::sin(PLAYERCONTROLS_FRECUENCY*m_ticksFloating);
         ++m_ticksFloating;
     }
*/



     //std::cout << m_floating << ":" << m_ticksFloating << "\t"
     //          << m_bouncing << ":" << m_ticksBouncing << std::endl;

}

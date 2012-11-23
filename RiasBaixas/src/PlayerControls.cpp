#include <PlayerControls.h>


PlayerControls::PlayerControls()
{
    m_left = false;
    m_right = false;
    m_speedUp = false;
    m_floating = true;
    m_ticksFloating = 0;
    m_ticksBouncing = 0;
}

void PlayerControls::move(ngl::Vec3 &_pos, ngl::Vec4 &_rot, ngl::Vec3 &_vel, float &_maxSpeed, const bool _jumping, const degreesOfFreedom _dof)
{
    std::cout << "PlayerControls: player controlling [" << m_left << " "<< m_speedUp << " "<< m_right << "]"<< std::endl;


    if (_jumping)
        std::cout << "it jumps" << std::endl;
    else
    {

        //MOVING IN X

        if (m_left && !m_right)
        {
            //comber left
            _vel.m_x = -PLAYERCONTROLS_LOWSPEED;
            _rot.m_y += PLAYERCONTROLS_CAMBER_STEP;
            _rot.m_x -= PLAYERCONTROLS_CAMBER_STEP;
        }

        if (m_right && !m_left)
        {
            //comber right
            _vel.m_x = PLAYERCONTROLS_LOWSPEED;
            _rot.m_y -= PLAYERCONTROLS_CAMBER_STEP;
            _rot.m_x += PLAYERCONTROLS_CAMBER_STEP;
        }

        //recover velocity and comber
        if (!m_left && !m_right)
        {
            //recover velocity
            _vel.m_x = 0;
            //recover comber anti-right
            if (_rot.m_y<90) _rot.m_y += PLAYERCONTROLS_CAMBER_STEP;
            if (_rot.m_x>0) _rot.m_x -= PLAYERCONTROLS_CAMBER_STEP;
            //recover comber anti-left
            if (_rot.m_y>90) _rot.m_y -= PLAYERCONTROLS_CAMBER_STEP;
            if (_rot.m_x<0) _rot.m_x += PLAYERCONTROLS_CAMBER_STEP;
        }

        //MOVING IN Z

        //accelerating
        if (m_speedUp)
            _vel.m_z -= PLAYERCONTROLS_ACCELERATION;
        else
            _vel.m_z += PLAYERCONTROLS_ACCELERATION;

        _vel.m_z = std::max(std::abs(_vel.m_z), (float)PLAYERCONTROLS_LOWSPEED);
        _vel.m_z = -std::min(std::abs(_vel.m_z), (float)PLAYERCONTROLS_HIGHSPEED);

        if (m_speedUp && !m_bouncing)
        {
            m_floating = false;
            _vel.m_y = PLAYERCONTROLS_ACCELERATION;
        }

        if (_vel.m_z == PLAYERCONTROLS_HIGHSPEED && _pos.m_y >= PLAYERCONTROLS_EMERSION_HIGH && !m_bouncing)
        {
            _vel.m_y = 0;
            m_bouncing = true;
            m_ticksBouncing = 0;
        }

        //bouncing
        if (m_bouncing)
        {
            _vel.m_y = PLAYERCONTROLS_EMERSION_HIGH + std::abs(PLAYERCONTROLS_AMPLITUDE_BOUNCING*std::cos(PLAYERCONTROLS_FRECUENCY*m_ticksBouncing));
             ++m_ticksBouncing;
            if (m_ticksBouncing>M_PI)
                m_ticksBouncing=0;
        }

        //decelerating
        if (!m_speedUp && _pos.m_y > 0 && !m_floating)
        {
            m_bouncing = false;
            _vel.m_y -= PLAYERCONTROLS_ACCELERATION;
        }

        if (_vel.m_z == PLAYERCONTROLS_LOWSPEED && _pos.m_y <= 0 && !m_floating)
        {
            _vel.m_y = 0;
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
        _pos.m_x = std::max(-SEA_WIDTH/(float)2, _pos.m_x);
        _pos.m_x = std::min(SEA_WIDTH/(float)2, _pos.m_x);
        _rot.m_y = std::max(90-(float)PLAYERCONTROLS_CAMBER, _rot.m_y);
        _rot.m_y = std::min(90+(float)PLAYERCONTROLS_CAMBER, _rot.m_y);
        _rot.m_x = std::max((float)-PLAYERCONTROLS_CAMBER, _rot.m_x);
        _rot.m_x = std::max((float)PLAYERCONTROLS_CAMBER, _rot.m_x);


    }

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

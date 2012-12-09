#ifndef PLAYERCONTROLS_H
#define PLAYERCONTROLS_H

/**
 * @file PlayerControls.h
 * @brief implements the movement of an object according with the user input
 */

#include "Controller.h"

#define PLAYERCONTROLS_HIGHSPEED 0.25
#define PLAYERCONTROLS_HIGHSPEED_X 0.2
#define PLAYERCONTROLS_EMERSION_HIGH 0.2
#define PLAYERCONTROLS_LATERAL_STREAM_FORCE 0.03
#define PLAYERCONTROLS_AMPLITUDE_BOUNCING 0.008
#define PLAYERCONTROLS_FRECUENCY_BOUNCING M_PI/60

/**
 * @class PlayerControls
 * @brief implements the movement of an object according with the user input
 */
class PlayerControls : public Controller
{
private:
    /**
     * @brief the movement goes towards the left
     */
    bool m_left;
    /**
     * @brief the movement goes towards the right
     */
    bool m_right;
    /**
     * @brief the user is speeding up
     */
    bool m_speedUp;
    /**
     * @brief the controller is in state floating
     */
    bool m_floating;
    /**
     * @brief the controller is in state bouncing
     */
    bool m_bouncing;
    /**
     * @brief the controller is in state emerging
     */
    bool m_emerging;
    /**
     * @brief the controller is in state immersing
     */
    bool m_immersing;
    /**
     * @brief the controller is in state jumping
     */
    bool m_jumping;
    /**
     * @brief ticks to track state of bouncing
     */
    int m_ticksBouncing;
    /**
     * @brief ticks to track state of jumping
     */
    int m_ticksJumping;

public:
    PlayerControls();
    void setLeft(bool _pressed) { m_left = _pressed; }
    void setRight(bool _pressed) { m_right = _pressed; }
    void setSpeedUp(bool _pressed) { m_speedUp = _pressed; }
    virtual void move();
};

#endif // PLAYERCONTROLS_H

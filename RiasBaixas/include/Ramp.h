#ifndef RAMP_H
#define RAMP_H

/**
 * @file Ramp.h
 * @brief Object that will apply a jumping force (class in construction)
 */
#include <Object.h>

/**
 * @class Ramp
 * @brief Object that will apply a jumping force (class in construction)
 */
class Ramp : public Object
{
private:
    int m_slope;
};

#endif // RAMP_H

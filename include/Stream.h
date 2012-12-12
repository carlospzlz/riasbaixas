#ifndef STREAM_H
#define STREAM_H

/**
 * @file Stream.h
 * @brief Object that will apply an acceleration force/increase maximum speed(class in construction)
 */
#include <Object.h>


/**
 * @class Stream
 * @brief Object that will apply an acceleration force/increase maximum speed(class in construction)
 */
class Stream : public Object
{
private:
    float speedUp;
    int effectTime;
};

#endif // STREAM_H

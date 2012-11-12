#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <ngl/Vec3.h>

class Controller
{

public:
    void move(ngl::Vec3 _position, ngl::Vec3 _velocity) { };
    //void virtual handleCollision(ngl::Vec3 _position, ngl::Vec3 _velocity, ngl::Vec3 _obstaclePosition,
      //                   int _obsXSize, int _obsYSize, int _obsZSize) { };

};

#endif // CONTROLLER_H

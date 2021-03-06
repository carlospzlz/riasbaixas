#include "BSpherePE.h"

void BSpherePE::checkCollision(Object *_o1, Object *_o2)
{
    //std::cout << "Cheking " << _o1->getType() << " with " << _o2->getType() << " and...";

    if (thereIsCollision(*_o1,*_o2))
    {
        //std::cout << " COLLISION" << std::endl;
        _o1->setCollided(true);
        _o2->setCollided(true);

        /** Now the six different directions of the collision are checked to
        * update the degrees of freedom and then to fix the position of each
        * object. We use the projections and the slopes to make the cheks. */

        ngl::Vec4 position1 = _o1->getPosition();
        ngl::Vec4 position2 = _o2->getPosition();

        //COLLISION (RELATIVE TO THE FIRST OBJECT)
        collisionData collision;

        //COLLISION PROJECTION FROM THE FRONT (OVER PLANE XY)
        collisionProjection front;
        front.up = front.down = front.left = front.right = false;
        calculateCollisionProjection(front, position1.m_x, position1.m_y, position2.m_x, position2.m_y);
        //std::cout << "FRONT " << front.left << front.right << front.up << front.down << std::endl;

        //COLLISION PROJECTION FROM THE TOP (OVER PLANE XZ)
        collisionProjection top;
        top.up = top.down = top.left = top.right = false;
        calculateCollisionProjection(top, position1.m_x, -position1.m_z, position2.m_x, -position2.m_z);
        //std::cout << "TOP " << top.left << top.right << top.up << top.down << std::endl;

        //COLLISION PROJECTION FROM THE RIGHT SIDE (OVER PLANE ZY)
        collisionProjection right;
        right.up = right.down = right.left = right.right = false;
        calculateCollisionProjection(right, -position1.m_z, position1.m_y, -position2.m_z, position2.m_y);
        //std::cout << "RIGHT " << right.left << right.right << right.up << right.down << std::endl;

        /*
        collision.up = front.up && right.up;
        collision.down = front.down && right.down;
        collision.left = front.left && top.left;
        collision.right = front.right && top.right;
        collision.forward = top.up && right.right;
        collision.backward = top.down && right.left;
        **/

        /*CALCULATE DEGREES FO FREEDOM SIMPLER APPROACH*/
        collision.left = top.left;
        collision.right = top.right;
        collision.forward = top.up;
        collision.backward = top.down;

        //std::cout << "COLLISION {" << collision.left << collision.right << collision.forward <<
        //             collision.backward << collision.backward << collision.forward << "}" << std::endl;

        //FIX POSITIONS
        /******* FIRST APPROACH*************
        if (collision.left || collision.right)
        {
            if (_o1->getMass()!=0)
            {
                position1.m_x = _o1->getPreviousPos().m_x;
                _o1->setPosition(position1);
            }
            if (_o2->getMass()!=0)
            {
                position1.m_x = _o1->getPreviousPos().m_x;
                _o2->setPosition(position2);
            }
        }
        else if (collision.backward || collision.forward)
        {
            if (_o1->getMass()!=0)
            {
                position1.m_z = _o1->getPreviousPos().m_z;
                _o1->setPosition(position1);
            }
            if (_o2->getMass()!=0)
            {
                position1.m_z = _o1->getPreviousPos().m_z;
                _o2->setPosition(position2);
            }
        }
        else if (collision.up || collision.down)
        {
            if (_o1->getMass()!=0)
            {
                position1.m_y = _o1->getPreviousPos().m_y;
                _o1->setPosition(position1);
            }
            if (_o2->getMass()!=0)
            {
                position1.m_y = _o1->getPreviousPos().m_y;
                _o2->setPosition(position2);
            }
        }******************************************/

        //FIX POSITIONS
        /******* SECOND APPROACH*************
        if (collision.left)
        {
            if ((_o1->getMass()!=0) && (position1.m_x<_o1->getPreviousPos().m_x))
                //fix
                _o1->setPosition(position1);
            if ((_o2->getMass()!=0) && (position2.m_x>_o2->getPreviousPos().m_x))
                //fix
                _o2->setPosition(position2);
        }
        else if (collision.right)
        {
            if ((_o1->getMass()!=0) && (position1.m_x>_o1->getPreviousPos().m_x))
                //fix
                _o1->setPosition(position1);
            if ((_o2->getMass()!=0) && (position2.m_x<_o2->getPreviousPos().m_x))
                //fix
                _o2->setPosition(position2);
        }
        else if (collision.forward)
        {
            if ((_o1->getMass()!=0) && (position1.m_z<_o2->getPreviousPos().m_z))
                _o1->setPosition(position1);
            if ((_o2->getMass()!=0) && (position2.m_z>_o2->getPreviousPos().m_z))
                _o2->setPosition(position2);
        }
        else if (collision.backward)
        {
            if ((_o1->getMass()!=0) && (position1.m_z>_o2->getPreviousPos().m_z))
                _o1->setPosition(position1);
            if ((_o2->getMass()!=0) && (position2.m_z<_o2->getPreviousPos().m_z))
                _o2->setPosition(position2);
        }
        ******************************************/



        //UPDATE VELOCITIES AND DEGREES OF FREEDOM OF BOTH OBJECTS
        //DO NOT TOUCH THE VELOCITY!!
        ngl::Vec4 velocity1 = _o1->getVelocity();
        ngl::Vec4 velocity2 = _o2->getVelocity();
        float factor = 0.5;

        if (collision.left || collision.right)
        {
            // X AXIS
            if (_o1->getMass()==0)
            {
                //velocity2.m_x = 0;
                //_o2->setVelocity(velocity2);
                if (collision.left)
                    _o2->getDOF().right = false;
                else
                    _o2->getDOF().left = false;
            }
            else if (_o2->getMass()==0)
            {
                //velocity1.m_x = 0;
                //_o1->setVelocity(velocity1);
                if (collision.left)
                    _o1->getDOF().left = false;
                else
                    _o1->getDOF().right = false;
            }
            else
            //Both are dynamic objects
            {
                _o1->setVelocity(ngl::Vec3(factor*(velocity1.m_x+velocity2.m_x),velocity1.m_y, velocity1.m_z));
                _o2->setVelocity(ngl::Vec3(factor*(velocity1.m_x+velocity2.m_x),velocity2.m_y, velocity2.m_z));
                //OLD CALCULATION
                //_o1->setVelocity(factor*(velocity1+velocity2));
                //_o2->setVelocity(factor*(velocity2+velocity1));
                if (collision.left)
                {
                    _o1->getDOF().left = false;
                    _o2->getDOF().right = false;
                }
                else
                //(collision.right)
                {
                    _o1->getDOF().right = false;
                    _o2->getDOF().left = false;
                }
            }
        }
        else if (collision.backward || collision.forward)
        {
            //Z AXIS
            if (_o1->getMass()==0)
            {
                //velocity2.m_z = 0;
                //_o2->setVelocity(velocity2);
                if (collision.backward)
                    _o2->getDOF().forward = false;
                else
                    _o2->getDOF().backward = false;
            }
            else if (_o2->getMass()==0)
            {
                //velocity1.m_z = 0;
                //_o1->setVelocity(velocity1);
                if (collision.backward)
                    _o1->getDOF().backward = false;
                else
                    _o1->getDOF().forward = false;
            }
            else
            //Both are dynamic objects
            {
                _o1->setVelocity(ngl::Vec3(velocity1.m_x,velocity1.m_y, factor*(velocity1.m_z+velocity2.m_z)));
                _o2->setVelocity(ngl::Vec3(velocity2.m_x,velocity2.m_y, factor*(velocity1.m_z+velocity2.m_z)));
                //OLD CALCULATION
                //_o1->setVelocity(factor*(velocity1+velocity2));
                //_o2->setVelocity(factor*(velocity2+velocity1));
                if (collision.forward)
                {
                    _o1->getDOF().forward = false;
                    _o2->getDOF().backward = false;
                }
                else
                //(collision.right)
                {
                    _o1->getDOF().backward = false;
                    _o2->getDOF().forward = false;
                }
            }
        }
        else if (collision.up || collision.down)
        {
            //Y AXIS
            if (_o1->getMass()==0)
            {
                //velocity2.m_y = 0;
                //_o2->setVelocity(velocity2);
                if (collision.up)
                    _o2->getDOF().down = false;
                else
                    _o2->getDOF().up = false;
            }
            else if (_o2->getMass()==0)
            {
                //velocity1.m_y = 0;
                //_o1->setVelocity(velocity1);
                if (collision.up)
                    _o1->getDOF().up = false;
                else
                    _o1->getDOF().down = false;
            }
            else
            //Both are dynamic objects
            {
                _o1->setVelocity(factor*(velocity1+velocity2));
                _o2->setVelocity(factor*(velocity2+velocity1));
                if (collision.up)
                {
                    _o1->getDOF().up = false;
                    _o2->getDOF().down = false;
                }
                else
                //(collision.right)
                {
                    _o1->getDOF().down = false;
                    _o2->getDOF().up = false;
                }
            }
        }

        //FIX POSITIONS
        //THIRD APPROACH

        if ((!_o1->getDOF().left) && (_o1->getPosition().m_x<_o1->getPreviousPos().m_x))
            _o1->setPosition(ngl::Vec3(_o1->getPreviousPos().m_x, _o1->getPosition().m_y, _o1->getPosition().m_z));
        if ((!_o1->getDOF().right) && (_o1->getPosition().m_x>_o1->getPreviousPos().m_x))
            _o1->setPosition(ngl::Vec3(_o1->getPreviousPos().m_x, _o1->getPosition().m_y, _o1->getPosition().m_z));
        if ((!_o1->getDOF().forward) && (_o1->getPosition().m_z<_o1->getPreviousPos().m_z))
            _o1->setPosition(ngl::Vec3(_o1->getPosition().m_x, _o1->getPosition().m_y, _o1->getPreviousPos().m_z));
        if ((!_o1->getDOF().backward) && (_o1->getPosition().m_z>_o1->getPreviousPos().m_z))
            _o1->setPosition(ngl::Vec3(_o1->getPosition().m_x, _o1->getPosition().m_y, _o1->getPreviousPos().m_z));


        if ((!_o2->getDOF().left) && (_o2->getPosition().m_x<_o2->getPreviousPos().m_x))
            _o2->setPosition(ngl::Vec3(_o2->getPreviousPos().m_x, _o2->getPosition().m_y, _o2->getPosition().m_z));
        if ((!_o2->getDOF().right) && (_o2->getPosition().m_x>_o2->getPreviousPos().m_x))
            _o2->setPosition(ngl::Vec3(_o2->getPreviousPos().m_x, _o2->getPosition().m_y, _o2->getPosition().m_z));
        if ((!_o2->getDOF().forward) && (_o2->getPosition().m_z<_o2->getPreviousPos().m_z))
            _o2->setPosition(ngl::Vec3(_o2->getPosition().m_x, _o2->getPosition().m_y, _o2->getPreviousPos().m_z));
        if ((!_o2->getDOF().backward) && (_o2->getPosition().m_z>_o2->getPreviousPos().m_z))
            _o2->setPosition(ngl::Vec3(_o2->getPosition().m_x, _o2->getPosition().m_y, _o2->getPreviousPos().m_z));

        _o1->collisionEvent(*_o2);
        _o2->collisionEvent(*_o1);

    }
    // else do nothing, it might have collided with other objects
    //std::cout << " NOTHING" << std::endl;
}

bool BSpherePE::thereIsCollision(Object const &_o1, const Object &_o2)
{
    float distance = std::sqrt(std::pow(_o1.getPosition().m_x-_o2.getPosition().m_x, 2) +
                               std::pow(_o1.getPosition().m_y-_o2.getPosition().m_y, 2) +
                               std::pow(_o1.getPosition().m_z-_o2.getPosition().m_z, 2) );
    return distance < (_o1.getBSRadius()+_o2.getBSRadius());
}

void BSpherePE::calculateCollisionProjection(collisionProjection &_projection, float _x1, float _y1, float _x2, float _y2)
{
    //std::cout << "COLLISION PROJECTION OF: " << "(" <<_x1 <<", "<< _y1 << ") ("<< _x2 <<", "<< _y2 <<")" << std::endl;

    float slope;
    if (_x1!=_x2)
    {
        slope = (_y2-_y1) / (_x2-_x1);

        //std::cout << "SLOPE: " << slope << std::endl;

        if (_x1<_x2)
        {
            if (slope>1)
                _projection.up = true;
            else if (slope>-1)
                _projection.right = true;
            else
                _projection.down = true;
        }
        else
        {
            if (slope>1)
                _projection.down = true;
            else if (slope>-1)
                _projection.left = true;
            else
                _projection.up = true;
        }
    }
    else
    {
        if (_y1<_y2)
            _projection.up = true;
        else
            _projection.down = true;
    }
}

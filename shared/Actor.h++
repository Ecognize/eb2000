#ifndef _EB2K_ACTOR_HPP_
#define _EB2K_ACTOR_HPP_

#include "Vector.h++"
#include "Point.h++"

class Actor
{
    public:
        Actor(unsigned int);
        
        /* Селекторы и модификаторы */
        unsigned int lastUpdate() const { return _lastUpdate; }
        const Point& position() const { return _pos; }
        const Vector& velocity() const { return _vel; }
        /* TODO: Так ли прямо? */
        Point& position() { return _pos; }
        Vector& velocity() { return _vel; }
        
        /* Пересчет положения, аргумент — текущее игровое время */
        void updatePosition(unsigned int newtime);
        
        /* TODO: селектор класса для определения размеров и графики */
        
    private:
        /* Геометрия — вектор скорости и положение */
        Vector _vel;
        Point _pos;
        
        /* Время последнего просчета координат в игровых миллисекундах */
        unsigned int _lastUpdate;
};

#endif

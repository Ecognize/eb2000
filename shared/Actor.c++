#include "Actor.c++"
#include <cassert>

void Actor::updatePosition(unsigned int newtime)
{
    /* Высчитываем разницу во времени */
    unsigned int delta=newtime-_lastUpdate;
    assert(delta>0);
    /* Обновляем координаты и время */
    _pos+=_vel*delta;
    _lastUpdate=newtime;
}

void Actor::updateVelocity(unsigned int newtime,const Vector& vel)
{
    /* Доделываем остаток непросчитанного движения */
    updatePosition(newtime);
    /* Запоминаем новый вектор */
    _vel=vel;
}

void Actor::translocate(unsigned int newtime,const Vector& point)
{
    /* Запоминаем новое положение и сбрасываем счетчик времени */
    _pos=point;
    _lastUpdate=newtime;
}

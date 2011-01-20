#include "Actor.h++"
#include <cassert>

/* Конструкция */
Actor::Actor(unsigned int id,const ActorClass& classid, 
             unsigned int birthtime, const Vector& pos,const Vector &vel) :
                _pos(pos),_vel(vel),_lastUpdate(birthtime),
                _classdef(classid),_handle(id)
{}

Actor::Actor(const Actor& p,unsigned int id, unsigned int birthtime)
    : _pos(p._pos),_vel(p._vel), _lastUpdate(birthtime),
      _classdef(p._classdef),_handle(id)
{}


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

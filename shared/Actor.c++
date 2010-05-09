#include "Actor.c++"
#include <cassert>

/* Конструкция */
Actor::Actor(Scene& parent,int classid, const Vector& pos,const Vector &vel) 
    : _parent(parent),_pos(pos),_vel(vel),
      _classdef(ClassLibrary::instance().classById(classid)),_handle(parent.requestHandle(this))
{}

Actor::Actor(const Actor& p)
    : _parent(p._parent),_pos(p._pos),_vel(p._vel),
      _classdef(p._classdef),_handle(p._parent.requestHandle(this))
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

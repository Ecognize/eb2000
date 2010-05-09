#ifndef _EB2K_ACTOR_HPP_
#define _EB2K_ACTOR_HPP_

#include "Vector.h++"
#include "Point.h++"
#include "ActorClass.h++"

class Scene;

class Actor
{
    public:
        /* Конструкция */
        Actor(Scene& parent,int classid, const Vector& pos=Vector(),const Vector &vel=Vector);
        Actor(const Actor& p);
        
        /* Селекторы */
        unsigned int lastUpdate() const { return _lastUpdate; }
        const Vector& position() const { return _pos; }
        const Vector& velocity() const { return _vel; }
        unsigned int handle() const { return _handle; }
        
        /* Пересчет положения, аргумент — текущее игровое время */
        void updatePosition(unsigned int newtime);
        /* Изменение вектора движения */ // TODO: прыжки героя
        void updateVelocity(unsigned int newtime,const Vector& vel);
        /* Мгновенное перемещение */
        void translocate(unsigned int newtime,const Vector& point);
        
        /* Селектор класса для определения размеров и графики */
        const ActorClass& classDef() const { return _classdef; }
        
    private:
        /* Геометрия — вектор скорости и положение */
        Vector _vel; // NB: игровых едениц в игровую миллисекунду
        Vector _pos;
        /* Внутренний номер объекта, присваивается менеджером */
        const unsigned int _handle;
        
        /* Отсылка на родительскую сцену */
        Scene& _parent;
        
        /* Ссылка на класс */
        const ActorClass& _classdef;
        
        /* Время последнего просчета координат в игровых миллисекундах */
        unsigned int _lastUpdate;
};

#endif

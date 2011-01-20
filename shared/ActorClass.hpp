#ifndef _EB2K_ACTORCLASS_HPP_
#define _EB2K_ACTORCLASS_HPP_

#include <list>

//TODO: комментарии
class ActorClass
{
    public:
        /* Конструкция */
        ActorClass(int i,double w, double h) : _id(i), _w(w), _h(h) {}
        /* Внутренний номер класса */
        int id() const { return _id; }
        /* Линейные размеры */
        double width() const { return _w; }
        double height() const { return _h; }
        
    private:
        int _id;
        double _w;
        double _h;
};

class ClassLibrary : public std::list<ActorClass>
{
    public:
        static ClassLibrary& instance();
        
        const ActorClass& classById(int) const { return back();/* STUB!! */ }
    private:
        ClassLibrary() {} 
};

#endif

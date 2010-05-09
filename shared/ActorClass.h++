#ifndef _EB2K_ACTORCLASS_HPP_
#define _EB2K_ACTORCLASS_HPP_

#include <list>

//TODO: комментарии
class ActorClass
{
    public:
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

class ClassLibrary : public std::list<const ActorClass&>
{
    public:
        static ActorClass& instance();
        
        const ActorClass& getClassById(int) const;
    private:
        ClassLibrary();
};

#endif

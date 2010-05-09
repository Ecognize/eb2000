#ifndef _EB2K_ACTORCLASS_HPP_
#define _EB2K_ACTORCLASS_HPP_

//TODO: комментарии
class ActorClass
{
    public:
        /* Внутренний номер класса */
        int id() const;
        /* Линейные размеры */
        double width() const;
        double height() const;
    private:
        ActorClass();
};

class ClassLibrary
{
    // TODO: синглтон
    public:
        const ActorClass& getClassById(int) const;
};

#endif

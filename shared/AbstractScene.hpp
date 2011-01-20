#ifndef _EB2K_ABSTRACT_SCENE_HPP_
#define _EB2K_ABSTRACT_SCENE_HPP_

#include <list>

template <class ActorType> class AbstractScene
{
    public:
        /* TODO: делегация итераторов, typedef-ы */
    private:
        std::list<ActorType *> _actorlist;
};

#endif

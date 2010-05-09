#include "ActorClass.h++"

static ActorClass& ActorClass::instance()
{
    static ActorClass cl;
    return cl;
}


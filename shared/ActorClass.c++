#include "ActorClass.h++"

ClassLibrary& ClassLibrary::instance()
{
    static ClassLibrary cl;
    return cl;
}


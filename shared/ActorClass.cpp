#include "ActorClass.hpp"

ClassLibrary& ClassLibrary::instance()
{
    static ClassLibrary cl;
    return cl;
}


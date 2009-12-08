#include "System.h++"

// TODO: commenting

System& System::instance()
{
    /* Creating a single instance */
    static System sys;
    return sys;
}


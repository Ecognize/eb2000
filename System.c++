#include "System.h++"

// TODO: комментарии

System& System::instance()
{
    /* Создаем единственную инстанцию */
    static System sys;
    return sys;
}


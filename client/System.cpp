#include "System.hpp"
#include <iostream>


#include "SDL.h"

/* Важные директивы препроцессора: 
    • REPORT_MODE — способ отображения сообщений
        => standard — стандартные потоки I/O
        => TODO
*/

// TODO: комментарии

/* Конструктор */
System::System() :
    soundOn(true),     // Звук по умолчанию включён
    mixerVolume(50)    // Средняя громкость
{
    loadConfig();       //Пропарсим конфиг
}

System& System::instance()
{
    /* Создаем единственную инстанцию */
    static System sys;
    return sys;
}

/* Функции оконной среды */
void System::messageBox(const std::string& s)
{
    #if (REPORT_MODE=="standard")
    std::cout<<s<<std::endl;
    #endif
}

void System::errorBox(const std::string& s)
{
    #if (REPORT_MODE=="standard")
    // TODO: локаль?
    std::cerr<<"ERROR: "<<s<<std::endl;
    #endif
}

bool System::questionBox(const std::string& s)
{
    #if (REPORT_MODE=="standard")
    std::cout<<s<<"? (yes/no)"<<std::endl;
    bool res=false;
    std::string& p="";
    for (;;)
    {
        std::cin>>p;
        // TODO: больше вариантов ответа, нечувствительность к регистру
        if (p=="no")
        {
            res=false; break;
        }
        else if (p=="yes")
        {
            res=true; break;
        }
        /* Только если первый ответ — фейл */
        std::cout<<"(yes/no)?"<<std::endl;
    }
    return res;
    #endif
}

// инициализация
static void System::init()
{
    if ( SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0 )
        errorBox("Error while initialising SDL.");
}

// завершаем работу
static void System::shutdown()
{
    SDL_Quit();
}

// Перенос Screen::_surface на физический экран
static void System::flipScreen()
{
    switch(screen.umode)
    {
        case _clean:
        break;


        case _vscreen:
        break;
    }
}

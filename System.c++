#include "System.h++"
#include <iostream>

/* Важные директивы препроцессора: 
    • REPORT_MODE — способ отображения сообщений
        => standard — стандартные потоки I/O
        => TODO
*/

// TODO: комментарии

/* Конструктор */
System::System() :
    //fail(false),       // Пока ещё всё хорошо
    hmax(false),       // Инфу от видеокарты ещё не получили и видеорежим ещё не установили, поэтому пусть пока будет false
    soundOn(true),     // Звук по умолчанию включён
    mixerVolume(50)   // Средняя громкость
{

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
    std::cout<<s<<"? (yes/no)"<<endl;
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
        std::cout<<"(yes/no)?"<<endl;
    }
    return res;
    #endif
}

// TODO: Заголовочный комментарий сюда
#ifndef _EB2K_SYSTEM_HPP_
#define _EB2K_SYSTEM_HPP_

//#include "Defs.h++"
//так пойдёт?
// elfy: вполне, только пока там ничего нет
// xela: будет

#include "Vector.h++"
#include "Screen.h++"
//#include "Sound.h++"


class Sound;     // WARNING: заглушка
class Sprite;    // то же самое


#include <string>

// TODO: DoxyGen
/*  Этот класс эмулирует процедурно ориентированный подход к низкоуровневым вызовам,
    при этом поддерживая всю иерархию классов приложения */
class System
{
    public:
        /* Проигрывание звука */
        static void playSound(const Sound&);                // Проигрывает непозиционированный звук
        static void playSound(const Sound&,const Point&);  // Проигрывает звук в указанной позиции
        
        /* Работа с видео */
        static int playableWidth();                         // Длина игрового поля, в пикселах
        static int playableHeight();                        // Высота игрового поля, в пикселах

        // Тогда уже пусть так
        // elfy: ненене, это делегация System::*Screen, в Screen::*Screen
        // рядовые классы не должны знать о скрине
        // xela: pilot.jpg
        // elfy: man Бублик

        static void flipScreen();                               // Вывод буфера на экран
        static void clearScreen();                              // Очистка экрана
        static void drawSprite(const Sprite&, const Point&);   // Нарисовать спрайт на данной позиции
        
        /* Функции оконной системы */
        static void messageBox(const std::string&);         // Окно сообщения
        static void errorBox(const std::string&);           // Окно ошибки
        static bool questionBox(const std::string&);        // Окно «да/нет» вопроса

        /* Управление конфигурацией */
        static void saveConfig();                            // Записать настройки в файл
        static void loadConfig();                            // Или прочитать их
        
        /* Функции системы */
        static void init();                                 // Начать работу; проинициализировать либы
        static void shutdown();                             // Завершить работу системы
    private:
        /* Ограничиваем доступ к инстанциированию и деинстанциированию */
        System();
        ~System();
        /* Доступ к синглтону */
        static System& instance();
        /* Запрещаем конструктор копирования и оператор присваивания */
        System(const System&) {}
        System& operator=(const System&) { return *this; }
        
    private:
        /* TODO: данные, заданные реализацией, писать сюда */

        /* Видео */ 
        Screen screen;

        /* Аудио */
    // а это тогда уже разве не в саунде?
    // elfy: можно и в саунде, только for the love of God, поставь в редакторе 4 пробела, а не таб,
    // или давай уже везде табы
    // xela: хорошо, 4 пробела. Я кстати начал входить во вкус)
    // elfy: кстати, как у тебя дела?
    // В какой сфере? :)
    // elfy: в сфере Огня :)))
        bool soundOn;                       // Включён ли звук?
        unsigned int mixerVolume;           // Главная громкость

        /* Прочее */
};

#endif

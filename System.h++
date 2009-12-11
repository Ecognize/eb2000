// TODO: Заголовочный комментарий сюда
#ifndef _EB2K_SYSTEM_HPP_
#define _EB2K_SYSTEM_HPP_

//#define _VERSION_        1            // Очень хотелось :) elfy: в отдельный хедер, и 0, релиза не было же
                                        //                   xela: а что будет ещё в том хедере?
//#define _CFG_HEADER_    "EB2KCFG"     // Хедер файла настроек, elfy: Господи, что это?
                                        //                       xela: "GGE sprites v.1.6" меня вдохновил )

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
        static void playSound(const Sound&,const Vector&);  // Проигрывает звук в указанной позиции
        
        /* Работа с видео */
        static int playableWidth();                         // Длина игрового поля, в пикселах
        static int playableHeight();                        // Высота игрового поля, в пикселах

	// Тогда уже пусть так
        // UPD: Может это тоже в скрин убрать?
        static void flipScreen(const Screen&);              // Вывод буфера на экран
        static void clearScreen(const Screen&);             // Очистка экрана
        
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

        /* Миша, все это хуйня! Это в скрине уже тогда должно быть! */
	// вот ^^^^^^

        /* Аудио */
	// а это тогда уже разве не в саунде?
        bool soundOn;                       // Включён ли звук?
        unsigned int mixerVolume;           // Главная громкость

        /* Прочее */
};

#endif
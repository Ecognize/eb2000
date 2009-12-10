// TODO: Заголовочный комментарий сюда
#ifndef _EB2K_SYSTEM_HPP_
#define _EB2K_SYSTEM_HPP_

#include "Vector.h++"
//#include "Sound.h++"
class Sound; // WARNING: заглушка

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
        static int playableWidth();     // Длина игрового поля, в пикселах
        static int playableHeight();    // Высота игрового поля, в пикселах
        
        /* Функции оконной системы */
        static void messageBox(const std::string&);     // Окно сообщения
        static void errorBox(const std::string&);       // Окно ошибки
        static bool questionBox(const std::string&);    // Окно «да/нет» вопроса
        
        /* Функции системы */
	static void init();				// Начать работу; проинициализировать либы
        static void shutdown();                         // Завершить работу системы
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
        /* TODO: данные, заданные реализацией писать сюда */
};

#endif

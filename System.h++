// TODO: Заголовочный комментарий сюда
#ifndef _EB2K_SYSTEM_HPP_
#define _EB2K_SYSTEM_HPP_

#define _VERSION_	    1        	// Очень хотелось :)
#define _CFG_HEADER_	"EB2KCFG"	// Хедер файла настроек

#include "Vector.h++"
//#include "Sound.h++"

class Sound; 	// WARNING: заглушка
class Sprite;	// то же самое
class VScreen;	// виртуальный экран

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

        static void flipScreen();	                        // Вывод буфера на экран
    	static void clearScreen();	                        // Очистка экрана
        
        /* Функции оконной системы */
        static void messageBox(const std::string&);         // Окно сообщения
        static void errorBox(const std::string&);           // Окно ошибки
        static bool questionBox(const std::string&);        // Окно «да/нет» вопроса

    	/* Управление конфигурацией */
	    static void saveConfig();			                // Записать настройки в файл
    	static void loadConfig();			                // Или прочитать их
        
        /* Функции системы */
	    static void init();			    	                // Начать работу; проинициализировать либы
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
	    unsigned int hx;					// Аппаратный максимальный x
    	unsigned int hy;					// Аппаратный максимальный y
    	unsigned int bpp;					// Сколько бит на пиксел
    	unsigned int vx;					// Виртуальный x
    	unsigned int vy;					// Виртуальный y
        bool hmax;                          // Используется максимальное разрешение?

    	/* Аудио */
        bool soundOn;                       // Включён ли звук?
    	unsigned int mixerVolume;			// Главная громкость

	    /* Прочее */
    	//bool fail;				        	// На случай критических ошибок
        // это нам нахрен не надо, у нас исключения же!
};

#endif

#ifndef _EB2K_SCREEN_HPP
#define _EB2K_SCREEN_HPP

#include <vector>
#include <iostream>

#include "SDL.h"
//#include "Color.h++"


class VideoMode
{
    public:
        VideoMode(int w,int h,int bpp=24,bool f=false, int p=1280) : _x(w),_y(h),_bpp(bpp),_fullscreen(f),_pitch(p) {  }

        unsigned w()          const { return _x; }
        unsigned h()          const { return _y; }
        unsigned bpp()        const { return _bpp; }
        unsigned pitch()      const { return _pitch; }
        bool     fullscreen() const { return _fullscreen; }

        unsigned &w()           { return _x; }
        unsigned &h()           { return _y; }
        unsigned &bpp()         { return _bpp; }
        unsigned &pitch()       { return _pitch; }
        bool     &fullscreen()  { return _fullscreen; }


    private:
        /* Физические данные, описание видеорежима */
        unsigned int _x;                    // Аппаратный используемый x
        unsigned int _y;                    // Аппаратный используемый y
        unsigned int _bpp;                  // Сколько бит на пиксел
        unsigned int _pitch;                 // for SDL
        bool _fullscreen;                   // Во весь экран или окно?
};

class Screen
{
    public:
        Screen();
        ~Screen();

        //typedef enum umode {_clean, _vscreen};

        /* Пользовательские функции */
        void  setVideoMode(const VideoMode& mode);     // установить видеорежим
        //const VideoMode getMaxVideoMode() const;     // получить максимально возможный видеорежим
        const VideoMode& getVideoMode() const;         // получить текущий видеорежим
        void  setScaling(/*umode mode*/);              // установить параметры переноса буфера
        void  flipScreen();                            // перенести виртуальный буфер на экран
        void  clearScreen();                           // очистить экран

        /* Графика */
        void putPixel(unsigned int x, unsigned int y, Uint32& color);                              // Поставить точку
        template <class ColorType> ColorType getPixel(unsigned int x, unsigned int y);                                                 // Узнать цвет точки

        template <class ColorType> void line(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const ColorType& color);  // Линия
        template <class ColorType> void rect(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const ColorType& color);  // Рамка
        template <class ColorType> void bar(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const ColorType& color);   // Закрашенный квадрат

        SDL_Surface * getSurface();
    private:
        VideoMode currentMode;              // Информация о видеорежиме, используемом в данный момент
        bool hmax;                          // Используется ли максимальное разрешение?

        /* "Игровые" или виртуальные данные, описание игрового экрана */
        unsigned int vw;                    // Виртуальный x 
        unsigned int vh;                    // Виртуальный y
        unsigned int vratio;                // Размер точки для виртуального экрана

        static const int _base;             // для v-scaling, устанавливается в файле реализации

        void * buffer;

        SDL_Surface * _sdlsurface;          // SDL-буфер

        void _putpixel(SDL_Surface*,int,int,Uint32);     // поставить физическую точку

        // указатель
        void (Screen::*putpixel)(int,int,Uint32);

        // для разной глубины цвета (байтов на точку)
        void putpixel1(int, int, Uint32);
        void putpixel2(int, int, Uint32);
        void putpixel3(int, int, Uint32);
        void putpixel4(int, int, Uint32);

        /* Прочее */
        unsigned short fps;                 // Понты колотить :)
};

/* Предполагаемый вариант использования этого класса:

    vi my;          <-- elfy: Миша, это полное гавно! данные нужно инициализировать
    my.x = 1024;        xela: Похуй. Это написано как пример, и акцент тут на setScaling.
    my.y = 768;
    my.bpp = 32;

    setVideoMode(my);       <-- тут собсно устанавливаем видеорежим
    setScaling(_vscreen);   <-- а тут устанавливаются значения vx, vy, vratio:
                            vratio = my.x / _base;
                            vx = _base;
                            vy = y / vratio;

                            и сам буфер теперь выглядит так: _surface[vx][vy]

    Иначе говоря, размеры _surface определяются при вызове этой функции
    elfy: пока что молчу, но отвыкай от Си ---V
    
    setVideoMode(VideoMode(1024,768,32));
    или
    VideoMode v(1024,768,32);
    setVideoMode(v);

*/
#endif

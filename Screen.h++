#ifndef _EB2K_SCREEN_HPP
#define _EB2K_SCREEN_HPP

#include <vector>

#include "SDL.h"
#include "Color.h++"


class VideoMode
{
    public:
        VideoMode(int w,int h,int bpp=24) : _x(w),_y(h),_bpp(bpp) {  }
                                                                    
        unsigned w() const { return _x; }
        unsigned h() const { return _y; }
        unsigned bpp() const { return _bpp; }
    private:
    /* Физические данные, описание видеорежима */
    unsigned int _x;                    // Аппаратный используемый x
    unsigned int _y;                    // Аппаратный используемый y
    unsigned int _bpp;                  // Сколько бит на пиксел
};

class Screen
{
    public:
        Screen();
        ~Screen();

        /* Пользовательские функции */
        void setVideoMode(const VideoMode& mode);    // установить видеорежим
        const VideoMode getMaxVideoMode();           // получить максимально возможный видеорежим
        void setScaling(umode mode);                 // установить параметры переноса буфера

        /* Графика */
        void putPixel(unsigned int x, unsigned int y, const Color& color);                                  // Поставить точку
        Color getPixel(unsigned int x, unsigned int y);                                                     // Узнать цвет точки

        void line(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const Color& color);  // Линия
        void rect(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const Color& color);  // Рамка
        void bar(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const Color& color);   // Закрашенный квадрат

        // elfy: в прайвате его нельзя будет юзать. альзо, назови константы полицеприятнее шоле, раз даешь интерфейс
        // xela: например? чем тебе эти не нравятся? константы как константы.
        
        enum umode = {_clean, _vscreen};    // Используемый режим переноса виртуального буфера на экран:
                                            // _clean - все виртуальные точки == физическим
                                            // _vscreen - эмуляция 320x[200/240/256],
                                            // каждая физическая точка увеличивается в [vratio = hx/_base] раз
                                            // подробнее см. xela's features @ fraxos

    private:
        VideoMode currentMode;              // Информация о видеорежиме, используемом в данный момент
        bool hmax;                          // Используется ли максимальное разрешение?

        /* "Игровые" или виртуальные данные, описание игрового экрана */
        unsigned int vw;                    // Виртуальный x 
        unsigned int vh;                    // Виртуальный y
        unsigned int vratio;                // Размер точки для виртуального экрана
        
        static const int _base;             // для v-scaling, устанавливается в файле реализации

        /* Собсно сами точки */
        std::vector<Color> _surface;        // Экранный буфер
                                            // TODO: сделать его 2D

        SDL_Surface * _sdlsurface;          // SDL-буфер

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

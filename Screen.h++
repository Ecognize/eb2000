#ifndef _EB2K_SCREEN_HPP
#define _EB2K_SCREEN_HPP

// main comment:
// очень важный класс. :)

#include <vector>
//#include "Color.h++"

class Color;

typedef struct  // Пусть это будет именно struct
{
        /* Физические данные, описание видеорежима */
        unsigned int hx;                    // Аппаратный используемый x
        unsigned int hy;                    // Аппаратный используемый y
        unsigned int bpp;                   // Сколько бит на пиксел
} vi;

class Screen
{
    public:
        /* Пользовательские функции */
        static void setVideoMode(vi mode);
        static void setScaling(umode mode);
        vi getMaxVideoMode();

    private:
        vi currentMode;                     // Информация о видеорежиме, используемом в данный момент
        bool hmax;                          // Используется ли максимальное разрешение?

        /* "Игровые" или виртуальные данные, описание игрового экрана */
        unsigned int vx;                    // Виртуальный x 
        unsigned int vy;                    // Виртуальный y
        unsigned int vratio;                // Размер точки для виртуального экрана
        
        static const int _base;             // для v-scaling, устанавливается в файле реализации

        enum umode = {_clean, _vscreen};    // Используемый режим переноса виртуального буфера на экран:
                                            // _clean - все виртуальные точки == физическим
                                            // _vscreen - эмуляция 320x[200/240/256],
                                            // каждая физическая точка увеличивается в [vratio = hx/_base] раз
                                            // подробнее см. xela's features @ fraxos

        /* Собсно сами точки */
        std::vector<Color> _surface;        // Экранный буфер
                                            // TODO: сделать его 2D
        /* Прочее */
        unsigned short fps;                 // Понты колотить :)
};
#endif

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
        unsigned int x;                    // Аппаратный используемый x
        unsigned int y;                    // Аппаратный используемый y
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

/* Предполагаемый вариант использования этого класса:

    vi my;
    my.x = 1024;
    my.y = 768;
    my.bpp = 32;

    setVideoMode(my);       <-- тут собсно устанавливаем видеорежим
    setScaling(_vscreen);   <-- а тут устанавливаются значения vx, vy, vratio:
                            vratio = my.x / _base;
                            vx = _base;
                            vy = y / vratio;

                            и сам буфер теперь выглядит так: _surface[vx][vy]

    Иначе говоря, размеры _surface определяются при вызове этой функции

*/
#endif

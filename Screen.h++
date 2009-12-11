#ifndef _EB2K_SCREEN_HPP
#define _EB2K_SCREEN_HPP

#define _base	320    // для v-scaling

// main comment:
// очень важный класс. :)

#include <vector>
//#include "Color.h++" пока хз, нужно ли помещать структуры цвета в отдельный хедер
//Наверное, да, для тех же спрайтов, например.

// Описание одной точки
typedef struct 
{
    unsigned short r;
    unsigned short g;
    unsigned short b;
    unsigned short a;
}color;

class Screen
{

    private:
        /* Физические данные, описание видеорежима */
        unsigned int hx;                    // Аппаратный используемый x
        unsigned int hy;                    // Аппаратный используемый y
        unsigned int bpp;                   // Сколько бит на пиксел
        bool hmax;                          // Используется ли максимальное разрешение?

        /* "Игровые" или виртуальные данные, описание игрового экрана */
        unsigned int vx;                    // Виртуальный x 
        unsigned int vy;                    // Виртуальный y
        unsigned int vratio;                // Размер точки для виртуального экрана

        enum umode = {_clean, _vscreen};    // Используемый режим переноса виртуального буфера на экран:
                                            // _clean - все виртуальные точки == физическим
                                            // _vscreen - эмуляция 320x[200/240/256],
                                            // каждая физическая точка увеличивается в vratio = hx/_base раз
                                            // подробнее см. xela's features @ fraxos

        /* Собсно сами точки */
        /*
	//std::vector<color> _psurface;       // физический экран
        //std::vector<color> _vsurface;       // виртуальный экран
                                            // в зависимости от umode flipScreen() из System.h++ 
                                            // будет брать тот или другой экран*/
        std::vector<color> _surface;         // Что-то я загнал, экран/буфер у нас один )) и просто
                                             // umode это scaling флаг 

        /* Прочее */
        unsigned short fps;                 // Понты колотить :)
};
#endif
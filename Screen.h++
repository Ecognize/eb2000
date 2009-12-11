#ifndef _EB2K_SCREEN_HPP
#define _EB2K_SCREEN_HPP

// main comment:
// очень важный класс. :)

#include <vector>
//#include "Color.h++" пока хз, нужно ли помещать структуры цвета в отдельный хедер
//Наверное, да, для тех же спрайтов, например.

class Color;
/*
    xela: Ты уверен что нужен именно класс?
          меня беспокоит только проблема скорости копирования массива   
*/

class Screen
{
    public:
        /* Пользовательские функции */
        static void setVideoMode();
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
        
        static const int _base;             // для v-scaling, устанавливается в файле реализации
                                            /*          xela: ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ - да нифига, мы как раз
                                                        всё подстраиваем под 320 по иксам, а вот vratio уже в реализации.
                                                        что ты имеешь против константы в хедере? */

        enum umode = {_clean, _vscreen};    // Используемый режим переноса виртуального буфера на экран:
                                            // _clean - все виртуальные точки == физическим
                                            // _vscreen - эмуляция 320x[200/240/256],
                                            // каждая физическая точка увеличивается в [vratio = hx/_base] раз
                                            // подробнее см. xela's features @ fraxos

        /* Собсно сами точки */
        std::vector<Color> _surface;        // Экранный буфер
                                            // P.S: Как его сделать 2D? std::vector<vector <Color>> _surface ? И как тогда обращаться к нему?

        /* Прочее */
        unsigned short fps;                 // Понты колотить :)
};
#endif

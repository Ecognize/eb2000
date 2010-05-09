#ifndef _EB2K_SCREEN_CPP
#define _EB2K_SCREEN_CPP

#include "Screen.h++"

const int Screen::_base = 320;

/* Конструктор и деструктор */
Screen::Screen() : currentMode(800,600,16),umode(_vscreen)
{
    fullscreen = false;
}

~Screen::Screen()
{
    SDL_FreeSurface(_sdlsurface);
    _sdlsurface = NULL;
}



/* Работа с видеорежимами */

// Узнать (максимальный) используемый режим
const VideoMode Screen::getMaxVideoMode() const
{
    const SDL_VideoInfo* s = SDL_GetVideoInfo();
    return VideoMode(s.current_w, s.current_h, s->vfmt.bitsPerPixel);
}

// Узнать текущий используемый режим
const VideoMode& Screen::getVideoMode() const
{
    return currentMode;
}

// Установить видеорежим
void Screen::setVideoMode(const VideoMode& mode)
{
    // TODO: Сделать нормальные ошибки
    Uint32 flags = SDL_HWSURFACE;

    if(fullscreen)
        flags |= SDL_FULLSCREEN;

    int bpp = SDL_VideoModeOK(mode.x(), mode.y(), mode.bpp(), flags);  // Определяем оптимальную глубину цвета

    if (bpp == 0)   // Режим не доступен
    {
        std::cerr<<"Mode is not available.";
        //exit(-1);
    }

    _sdlsurface = SDL_SetVideoMode(mode.x(), mode.y(), bpp, flags);    // Установим режим

    if(_sdlsurface == NULL)
        std::cerr<<"Can not set videomode.";

    // Заполним инфо о режиме
    currentMode(mode.x(), mode.y(), bpp);
}

// Установить сглаживание
void Screen::setScaling(umode mode)
{
    switch(mode)
    {
        case _clean:
        vw = currentMode.x();
        vh = currentMode.y();
        umode = _clean;
        break;

        case _vscreen:
        vratio = currentMode.x() / _base;
        vw = _base;
        vh = currentMode.y() / vratio;
        umode = _vscreen;
        break;

        default:
        setScaling(_clean);
        break;
    }

    for (int i = 0; i < vh; i++ )
    {
        _surface.push_back( std::vector <Color>() );

        for(int j = 0; j < vw; j++ )
            _surface[i].push_back(Color::Black);
    }
    /* ^^^^ Setting size of _surface to [vw] * [vh])*/
}

// Перенести виртуальный буфер на физический экран, главный bottle-neck
void Screen::flipScreen()
{
    // Пока что забудем про umode и будем переписывать напрямую

    Uint8 *p;                                     // указатель на физический адрес пикселя для SDL
    Uint32 c;                                     // цвет для SDL
    Color point;                                  // текущая точка виртуального экрана
    int b = _sdlsurface->format->BytesPerPixel;   // байт на точку на физическом экране


    for(int y = 0; y < currentMode.y(); y ++)
        for(int x = 0; x < currentMode.x(); x ++)
        {
            point = _surface[x][y];                         // берём одну точку из нашего буфера
            p = (Uint8 *)s->pixels + y * s->pitch + x * z;  // считаем, куда её поставить

            /* определили цвет для SDL */
            c = SDL_MapRGB(_sdlsurface->format, point.r(), point.g(), point.b());

            /* ставим точку */
            switch(b)
            {
                case 1:
                *p = c;
                break;

                case 2:
                *(Uint16 *)p = c;
                break;

                case 3:
                if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                    p[0] = (c >> 16) & 0xff;
                    p[1] = (c >> 8)  & 0xff;
                    p[2] = c         & 0xff;
                } else {
                    p[0] = c         & 0xff;
                    p[1] = (c >> 8)  & 0xff;
                    p[2] = (c >> 16) & 0xff;
                }
                break;

                case 4:
                *(Uint32 *)p = c;
                break;
            }
        }
}

// Поставить точку
void Screen::putPixel(unsigned int x, unsigned int y, const Color& color) 
{
    _surface[x][y] = color;
}

// Узнать цвет точки
Color Screen::getPixel(unsigned int x, unsigned int y)
{
    return _surface[x][y];
}

/* Графические примитивы */

// Линия
void Screen::line(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const Color& color)
{
    int dy = y1 - y0;
    int dx = x1 - x0;
    int stepx, stepy;
    int fraction;

    if (dy < 0) { dy = -dy;  stepy = -1; } else { stepy = 1; }
    if (dx < 0) { dx = -dx;  stepx = -1; } else { stepx = 1; }

    dy <<= 1;              // dy == 2*dy
    dx <<= 1;              // dx == 2*dx

    putPixel(x0, y0, color);

    if (dx > dy)
    {
        fraction = dy - (dx >> 1);                         // == 2*dy - dx
        while (x0 != x1)
        {
            if (fraction >= 0)
            {
                y0 += stepy;
                fraction -= dx;                         
            }
            x0 += stepx;
            fraction += dy;
            putPixel(x0, y0, color);
        }
    } else {
        fraction = dx - (dy >> 1);
        while (y0 != y1)
        {
            if (fraction >= 0)
            {
                x0 += stepx;
                fraction -= dy;
            }
            y0 += stepy;
            fraction += dx;
            putPixel(x0, y0, color);
        }
    }
}

// Рамка
void Screen::rect(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const Color& color)
{
    int x = x0;

    for(x0; x0 <= x1; x0++)
    {
        putPixel(x0, y0, color);
        putPixel(x0, y0 + y1, color);
    }
    for(y0; y0 <= y1; y0++)
    {
        putPixel(x, y0, color);
        putPixel(x1, y0 + y1, color);
    }
}

// Квадрат
void Screen::bar(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const Color& color)
{
    for(x0; x0 <= x1; x0++ )
        for(y0; y0 <= y1; y0++ )
            putPixel(x0, y0, color);
}


#endif

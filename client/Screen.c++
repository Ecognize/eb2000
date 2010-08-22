#ifndef _EB2K_SCREEN_CPP
#define _EB2K_SCREEN_CPP

#include "Screen.h++"


const int Screen::_base = 320;

/* Конструктор и деструктор */
Screen::Screen() : currentMode(800,600,16,false)//,tmode(_vscreen)
{
    
}

Screen::~Screen()
{
    SDL_FreeSurface(_sdlsurface);
    _sdlsurface = NULL;
}



/* Работа с видеорежимами */
/*
// Узнать (максимальный) используемый режим
const VideoMode Screen::getMaxVideoMode() const
{
    const SDL_VideoInfo* s = SDL_GetVideoInfo();
    return VideoMode(s->current_w, s->current_h, s->vfmt.bitsPerPixel);
}*/

// Узнать текущий используемый режим
const VideoMode& Screen::getVideoMode() const
{
    return currentMode;
}

// Установить видеорежим
void Screen::setVideoMode(const VideoMode& mode)
{
    // TODO: Сделать нормальные ошибки (через исключения)
    Uint32 flags = SDL_HWSURFACE | SDL_DOUBLEBUF;

    if(mode.fullscreen())
        flags |= SDL_FULLSCREEN;

    int bpp = SDL_VideoModeOK(mode.w(), mode.h(), mode.bpp(), flags);  // Определяем оптимальную глубину цвета

    if (bpp == 0)   // Режим не доступен
    {
        throw "Mode is not available.";
        //exit(-1);
    }
    std::cout<<"Mode verified: "<<mode.w()<<"x"<<mode.h()<<"x"<<bpp<<std::endl;
    _sdlsurface = SDL_SetVideoMode(mode.w(), mode.h(), mode.bpp(), flags);    // Установим режим

    if(_sdlsurface == NULL)
        throw "Can not set videomode.";

    // Заполним инфо о режиме
    currentMode.w() = mode.w();
    currentMode.h() = mode.h();
    currentMode.bpp() = bpp;
}

// Установить сглаживание
void Screen::setScaling(/*umode mode*/)
{
    /*switch(mode)
    {
        case _clean:*/
        vw = currentMode.w();
        vh = currentMode.h();
        //tmode = _clean;
        /*break;

        case _vscreen:
        vratio = currentMode.w() / _base;
        vw = _base;
        vh = currentMode.h() / vratio;
        tmode = _vscreen;
        break;

        default:
        setScaling(_clean);
        break;
    }*/

    for (int i = 0; i < vh; i++ )
    {
        _surface.push_back( std::vector <Color>() );

        for(int j = 0; j < vw; j++ )
            _surface[i].push_back(Color::Black);
    }
    /* ^^^^ Setting size of _surface to [vw] * [vh])*/
}

void Screen::_putpixel(int x, int y, Uint32 pixel) 
{ 
    int bpp = _sdlsurface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)_sdlsurface->pixels + y * _sdlsurface->pitch + x * bpp;

    switch(bpp)
    {
        case 1:
        *p = pixel;
        break;

        case 2:
        *(Uint16 *)p = pixel;
        break;

        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            } else {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
        break;

        case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

// Перенести виртуальный буфер на физический экран, главный bottle-neck
void Screen::flipScreen()
{
    // Пока что забудем про umode и будем переписывать напрямую

    Uint32 c;                                       // цвет для SDL
    Color point;                                    // текущая точка виртуального экрана

    // заблокируем экран ( я без этого делал, но тут пусть будет)
    if ( SDL_MUSTLOCK(_sdlsurface) ) 
    {
        if ( SDL_LockSurface(_sdlsurface) < 0 ) 
            throw "Can't lock screen"; // %s\n", SDL_GetError()); 
    }

    for(int y = 0; y < currentMode.h(); y ++)
        for(int x = 0; x < currentMode.w(); x ++)
        {
            point = _surface[y][x];                         // берём одну точку из нашего буфера
            /* определим цвет для SDL */
            c = SDL_MapRGB(_sdlsurface->format, point.r(), point.g(), point.b());
            /* ставим точку */
            _putpixel(x, y, c);
        }
    // разблокируем обратно
    if ( SDL_MUSTLOCK(_sdlsurface) ) 
        SDL_UnlockSurface(_sdlsurface); 

    SDL_UpdateRect(_sdlsurface, 0, 0, 0, 0);//currentMode.w(), currentMode.h());
}

// очистка экрана
void Screen::clearScreen()
{
    for(int y = 0; y < vh; y++)
       for(int x = 0; x < vw; x++)
           _surface[y][x] = Color::Black;
    
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

    for(; x0 <= x1; x0++)
    {
        putPixel(x0, y0, color);
        putPixel(x0, y0 + y1, color);
    }
    for(; y0 <= y1; y0++)
    {
        putPixel(x, y0, color);
        putPixel(x1, y0 + y1, color);
    }
}

// Квадрат
void Screen::bar(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const Color& color)
{
    for(int y = y0; y <= y1; y++ )
        for(int x = x0; x <= x1; x++ )
            putPixel(x, y, color);
}


#endif

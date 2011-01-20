#ifndef _EB2K_SCREEN_CPP
#define _EB2K_SCREEN_CPP

#include "Screen.hpp"

// emulate 320x2xx screen
const int Screen::virtualb = 320;

/* Конструктор и деструктор */
Screen::Screen() : currentMode(800,600,16,false)
{
    sfmode = 0;    // drawing to virtual
}

Screen::~Screen()
{
    SDL_FreeSurface(context);
    context = NULL;
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
    Uint32 flags = SDL_OPENGL;

    if(mode.fullscreen())
        flags |= SDL_FULLSCREEN;

    int bpp = SDL_VideoModeOK(mode.w(), mode.h(), mode.bpp(), flags);  // Определяем оптимальную глубину цвета

    if (bpp == 0)   // Режим не доступен
    {
        throw "Mode is not available.";
        //exit(-1);
    }

    // TODO: make normal debug messages
    std::cout << "Mode verified: " << mode.w() << "x" << mode.h() << "x" << bpp << std::endl;
    context = SDL_SetVideoMode(mode.w(), mode.h(), mode.bpp(), flags);    // Установим режим
    
    if(context == NULL)
        throw "Can not set videomode.";

    // Заполним инфо о режиме
    currentMode.w() = mode.w();
    currentMode.h() = mode.h();
    currentMode.bpp() = bpp;

    // fill up virtual screen data
    virtualw = virtualb;
    virtuals = currentMode.w() / virtualb;
    virtualh = currentMode.h() / virtuals;

    // make vector
    for (int i = 0; i < virtualh * virtualw; i++)
        buffer.push_back(Color::Black);

    std::cout << "Virtual screen initialized: " << virtualw << "x" << virtualh << ", pixel size is " << virtuals << std::endl;
}

// get screen flipping mode
int Screen::getMode()
{
    return sfmode;
}

// set screen flipping mode
void Screen::setMode(int m)
{
    sfmode = m;
}

void Screen::flipEntireScreen()
{
    // Пока что забудем про umode и будем переписывать напрямую

    // заблокируем экран ( я без этого делал, но тут пусть будет)
   /* if ( SDL_MUSTLOCK(_sdlsurface) )
        if ( SDL_LockSurface(_sdlsurface) < 0 ) 
            throw "Can't lock screen"; // %s\n", SDL_GetError());*/

   /* for(int y = 0; y < currentMode.h(); y ++)
        for(int x = 0; x < currentMode.w(); x ++)
          (*putpixel)(_sdlsurface, x, y, _surface[x + vw * y]);
*/
      //memcpy(_sdlsurface->pixels, buffer, sizeof(_sdlsurface->pixels));
      //SDL_LockSurface(_sdlsurface);
      //_sdlsurface->pixels = buffer;
      //memcpy(_sdlsurface->pixels, buffer, sizeof(_sdlsurface->pixels));
      //SDL_UnlockSurface(_sdlsurface);
    // разблокируем обратно
    /*if ( SDL_MUSTLOCK(_sdlsurface) )
        SDL_UnlockSurface(_sdlsurface); */

    //currentMode.w(), currentMode.h());
    //SDL_BlitSurface(buffer, 0, _sdlsurface, 0);
    SDL_UpdateRect(context, 0, 0, 0, 0);
}

// очистка экрана
void Screen::clearScreen()
{
    /*for(int y = 0; y < vh; y++)
       for(int x = 0; x < vw; x++)
           _surface[x + vw * y] = Color::Black;*/
    
}

// Поставить точку
void Screen::putPixel(unsigned int x, unsigned int y, const Color &color)
{
   buffer[x + virtualw * y] = color;
}

// Узнать цвет точки
Color Screen::getPixel(unsigned int x, unsigned int y)
{
    return buffer.at(x + virtualw * y);
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

#ifndef _EB2K_SCREEN_CPP
#define _EB2K_SCREEN_CPP

#include "Screen.h++"


const int Screen::_base = 320;

/* Конструктор и деструктор */
Screen::Screen() : currentMode(800,600,16,false)//,tmode(_vscreen)
{
    buffer = NULL;
}


Screen::~Screen()
{
    SDL_FreeSurface(_sdlsurface);
    _sdlsurface = NULL;

    buffer = NULL;
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

    buffer = _sdlsurface->pixels;
    
    if(_sdlsurface == NULL)
        throw "Can not set videomode.";

    // Заполним инфо о режиме
    currentMode.w() = mode.w();
    currentMode.h() = mode.h();
    currentMode.bpp() = bpp;
    currentMode.pitch() = _sdlsurface->pitch;

    //buffer = _sdlsurface->pixels;
    
    // определим нужную процедуру для вывода точки
    switch(_sdlsurface->format->BytesPerPixel)
    {
        case 1:
        putpixel = &Screen::putpixel1;
        break;

        case 2:
        putpixel = &Screen::putpixel2;
        break;

        case 3:
        putpixel = &Screen::putpixel3;
        break;

        case 4:
        putpixel = &Screen::putpixel4;
        break;
    }
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

    /*for (int i = 0; i < vh; i++ )
    {
        _surface.push_back( std::vector <Color>() );

        for(int j = 0; j < vw; j++ )
            _surface[i].push_back(Color::Black);
    }*/
    /* ^^^^ Setting size of _surface to [vw] * [vh])*/
    int size = sizeof(Uint32) * vw * vh;
    std::cout<<"Allocating "<<size / 1024<<" Kb..."<<std::endl;

    //_surface = (Uint32 *)malloc(size);
}

SDL_Surface * Screen::getSurface()
{
    return _sdlsurface;
}
// Физический вывод точки: основная функция и оптимизированные варианты
void Screen::_putpixel(SDL_Surface *s,int x, int y, Uint32 pixel) 
{
    //(*putpixel)(s, x, y, pixel);
}

void Screen::putpixel1(int x, int y, Uint32 pixel)
{
   *((Uint8 *)buffer + y * currentMode.pitch() + x) = pixel;
}

void Screen::putpixel2(int x, int y, Uint32 pixel)
{
    *((Uint16 *)buffer + y * currentMode.pitch()/2 + x) = pixel;
}

void Screen::putpixel3(int x, int y, Uint32 pixel)
{
    Uint8 *p = (Uint8 *)buffer + y * currentMode.pitch() + x * 3;

    if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
        p[0] = (pixel >> 16) & 0xff;
        p[1] = (pixel >> 8) & 0xff;
        p[2] = pixel & 0xff;
    } else {
        p[0] = pixel & 0xff;
        p[1] = (pixel >> 8) & 0xff;
        p[2] = (pixel >> 16) & 0xff;
    }
}

void Screen::putpixel4(int x, int y, Uint32 pixel)
{
    *((Uint32 *)buffer + y * currentMode.pitch()/4 + x) = pixel;
}

// Перенести виртуальный буфер на физический экран, главный bottle-neck
void Screen::flipScreen()
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
    SDL_UpdateRect(_sdlsurface, 0, 0, 0, 0);
}

// очистка экрана
void Screen::clearScreen()
{
    /*for(int y = 0; y < vh; y++)
       for(int x = 0; x < vw; x++)
           _surface[x + vw * y] = Color::Black;*/
    
}

// Поставить точку
void Screen::putPixel(unsigned int x, unsigned int y, Uint32 &color)
{
   // _surface[x + vw * y] = color;
    (this->*putpixel)(x, y, color);
}

// Узнать цвет точки
template <class ColorType> ColorType Screen::getPixel(unsigned int x, unsigned int y)
{
    return 1;//surface[x + vw * y];
}

/* Графические примитивы */

// Линия
template <class ColorType> void Screen::line(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const ColorType& color)
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
template <class ColorType> void Screen::rect(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const ColorType& color)
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
template <class ColorType> void Screen::bar(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const ColorType& color)
{
    for(int y = y0; y <= y1; y++ )
        for(int x = x0; x <= x1; x++ )
            putPixel(x, y, color);
}


#endif

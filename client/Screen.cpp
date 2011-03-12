#ifndef _EB2K_SCREEN_CPP
#define _EB2K_SCREEN_CPP

#include "Screen.hpp"
#include <cstdlib>

// emulate 320x2xx screen
const int Screen::virtualb = 320;

/* Конструктор и деструктор */
Screen::Screen() : currentMode(800,600,16,false)
{
    sfmode = FLIP_VIRTUAL;    // drawing to virtual
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

// Установить видеорежим
void Screen::setVideoMode(const VideoMode& mode)
{
    // TODO: Сделать нормальные ошибки (через исключения)
    Uint32 flags = SDL_OPENGL;

    if(mode.fullscreen())
        flags |= SDL_FULLSCREEN;


    if (SDL_VideoModeOK(mode.w(), mode.h(), mode.bpp(), flags) == 0)   // Режим не доступен
    {
        // throw "Mode is not available.";
        std::cout << "mode is not available" << std::endl;
        exit(-1);
    }

    // TODO: make normal debug messages
    std::cout << "Mode verified: " << mode.w() << "x" << mode.h() << "x" << mode.bpp() << std::endl;
    context = SDL_SetVideoMode(mode.w(), mode.h(), mode.bpp(), flags);    // Установим режим
    
    if(context == NULL)
    {
        //throw "Can not set videomode.";
        std::cout << "can not set videomode" << std::endl;
        exit(-1);
    }

    // set window caption
    SDL_WM_SetCaption( "eb2k", NULL );

    // set few OpenGL flags
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);   // use double buffering
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho (0, mode.w(), mode.h(), 0, 0, 1);      // for pixel-precise
    glMatrixMode (GL_MODELVIEW);

    glDisable(GL_DITHER) ;
    glDisable(GL_DEPTH_TEST);                      // disable depth buffer
    glClear(GL_COLOR_BUFFER_BIT);                  // clear screen

    // Заполним инфо о режиме
    currentMode.w() = mode.w();
    currentMode.h() = mode.h();
    currentMode.bpp() = mode.bpp();

    // fill up virtual screen data
    virtualMode.bpp() = currentMode.w() / virtualb;           // declare the 320x2xx
    virtualMode.w() = currentMode.w() / virtualMode.bpp();    // but make actual wider
    virtualMode.h() = currentMode.h() / virtualMode.bpp();    // for full using of screen
    virtualMode.fullscreen() = currentMode.fullscreen();

    // make vector
    //for(unsigned int y = 0; y < virtualh; y++)
    //    for(unsigned int x = 0; x < virtualw; x++)
    //        buffer.insert(std::make_pair(Point(x,y), Color::Black));

    std::cout << "Virtual screen initialized: " <<
        virtualMode.w() << "x" << virtualMode.h() <<
        ", pixel size is " << virtualMode.bpp() << std::endl;
}

void Screen::makeQuad(const Point & point, const Color & color)
{
    glColor4ub(color.r(), color.g(), color.b(), color.a());
    
    glBegin(GL_QUADS);
        glVertex2i(point.x() * virtualMode.bpp(), point.y() * virtualMode.bpp());
        glVertex2i(point.x() * virtualMode.bpp() + virtualMode.bpp(), point.y() * virtualMode.bpp());
        glVertex2i(point.x() * virtualMode.bpp() + virtualMode.bpp(), point.y() * virtualMode.bpp() + virtualMode.bpp());
        glVertex2i(point.x() * virtualMode.bpp(), point.y() * virtualMode.bpp() + virtualMode.bpp());
    glEnd();
}

// get screen flipping mode
int Screen::getMode() { return sfmode; }

// set screen flipping mode
void Screen::setMode(int m) { sfmode = m; }

// get current screen dimensions depending on mode
const VideoMode& Screen::getCurrentMode() const
{
    if(sfmode == FLIP_VIRTUAL)
         return virtualMode;
    else return currentMode;
}

void Screen::flipEntireScreen()
{
   /* if(sfmode == FLIP_VIRTUAL)   // flip virtual screen
    {
        Color point;

        for(int y = 0; y < virtualh; y ++)
            for(int x = 0; x < virtualw; x ++)
            {
                point = buffer[x + virtualw * y];

               // makeQuad(x, y, point);
            }
    }
  */
    // update screen anyway
    SDL_GL_SwapBuffers();
    //SDL_UpdateRect(context, 0, 0, 0, 0);
}

// очистка экрана
void Screen::clearScreen()
{
    /*for(int y = 0; y < vh; y++)
       for(int x = 0; x < vw; x++)
           _surface[x + vw * y] = Color::Black;*/
        glClear(GL_COLOR_BUFFER_BIT);
    
}


// Поставить точку
void Screen::putPixel(const Point & point, const Color &color)
{
    if(sfmode == FLIP_VIRTUAL)
        makeQuad(point, color);
    else    // just put physical point
    {
        glColor4ub(color.r(), color.g(), color.b(), color.a());
        glBegin(GL_POINTS);
            glVertex2i(point.x(), point.y());
        glEnd();
    }
}

void Screen::putPixel(unsigned int x, unsigned int y, const Color &color)
{
    putPixel(Point(x, y), color);
}

// Узнать цвет точки
Color Screen::getPixel(unsigned int x, unsigned int y)
{
    return Color::Black;//buffer.at(x + virtualw * y);
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

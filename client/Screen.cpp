#ifndef _EB2K_SCREEN_CPP
#define _EB2K_SCREEN_CPP

#include "Screen.hpp"
#include <cstdlib>

// emulate 312x192 screen
const unsigned int Screen::vx = 312;
const unsigned int Screen::vy = 192;

/* Конструктор и деструктор */
Screen::Screen() : currentMode(800, 600, 16, false)
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
    ps = currentMode.w() / vx;      // determine point size for 312x192

    xshift = (currentMode.w() - (vx * ps)) / 2;
    yshift = (currentMode.h() - (vy * ps)) / 2;

    std::cout << "point size is " << ps << ", shift is " << xshift << "x" << yshift << std::endl;
}

void Screen::makeQuad(unsigned int x, unsigned int y, const Color & color)
{
    glColor4ub(color.r(), color.g(), color.b(), color.a());
    
    glBegin(GL_QUADS);
        glVertex2i(xshift + x * ps,      yshift + y * ps);
        glVertex2i(xshift + x * ps + ps, yshift + y * ps);
        glVertex2i(xshift + x * ps + ps, yshift + y * ps + ps);
        glVertex2i(xshift + x * ps,      yshift + y * ps + ps);
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
         return VideoMode(vx, vy, ps, currentMode.fullscreen());
    else return currentMode;
}

void Screen::flipScreen()
{
    SDL_GL_SwapBuffers();
}

// очистка экрана
void Screen::clearScreen()
{
    glClear(GL_COLOR_BUFFER_BIT);
}


// Поставить точку
void Screen::putPixel(unsigned int x, unsigned int y, const Color &color)
{
    if(sfmode == FLIP_VIRTUAL)
        makeQuad(x, y, color);
    else    // just put physical point
    {
        glColor4ub(color.r(), color.g(), color.b(), color.a());
        glBegin(GL_POINTS);
            glVertex2i(x, y);
        glEnd();
    }
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

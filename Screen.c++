#ifndef _EB2K_SCREEN_CPP
#define _EB2K_SCREEN_CPP

#include "Screen.h++"

const int Screen::_base = 320;

/* elfy: БЛДЖАД man инициализация */
Screen::Screen() : currentMode(800,600,16),umode(_vscreen)
{
    // чем же хуитища?
}

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

    /* здесь как-нибудь установить размеры _surface ([vw] * [xh])*/
}

void Screen::putPixel(unsigned int x, unsigned int y, const Color& color) 
{
    _surface[x][y] = color;
}

Color Screen::getPixel(unsigned int x, unsigned int y)
{
    return _surface[x][y];
}

// Графические примитивы

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

void Screen::bar(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const Color& color)
{
    for(x0; x0 <= x1; x0++ )
        for(y0; y0 <= y1; y0++ )
            putPixel(x0, y0, color);
}


#endif

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

void Screen::putPixel(unsigned int x, unsigned int y, Color color)
{
    _surface[x][y] = color;
}

Color Screen::getPixel(unsigned int x, unsigned int y)
{
    return _surface[x][y];
}

#endif
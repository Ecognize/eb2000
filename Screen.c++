#ifndef _EB2K_SCREEN_CPP
#define _EB2K_SCREEN_CPP

#include "Screen.h++"

const int Screen::_base = 320;

/* elfy: БЛДЖАД man инициализация */
Screen::Screen() : currentMode(800,600,16),umode(_vscreen)
{
    /*currentMode.x  = 800;
    currentMode.y  = 600;
    currentMode.bpp = 16;

    umode = _vscreen; === ХУИТИЩА */

}

#endif

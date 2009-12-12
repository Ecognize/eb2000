#ifndef _EB2K_SCREEN_CPP
#define _EB2K_SCREEN_CPP

#include "Screen.h++"

const int Screen::_base = 320;

Screen::Screen()
{
    currentMode.x  = 800;
    currentMode.y  = 600;
    currentMode.bpp = 16;

    umode = _vscreen;

}

#endif

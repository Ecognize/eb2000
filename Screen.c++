#ifndef _EB2K_SCREEN_CPP
#define _EB2K_SCREEN_CPP

#include "Screen.h++"

const int Screen::_base = 320;

Screen::Screen()
{
    info.x  = 800;
    info.y  = 600;
    info.bpp = 16;
}

#endif

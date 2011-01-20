#ifndef _EB2K_SCREEN_HPP
#define _EB2K_SCREEN_HPP

#include <vector>
#include <iostream>

#include "SDL.h"
#include "Color.hpp"


// video mode container
class VideoMode
{
    public:
        VideoMode(int w,int h,int bpp=24,bool f=false) : _x(w),_y(h),_bpp(bpp),_fullscreen(f) {  }

        unsigned w()          const { return _x; }
        unsigned h()          const { return _y; }
        unsigned bpp()        const { return _bpp; }
        bool     fullscreen() const { return _fullscreen; }

        unsigned &w()           { return _x; }
        unsigned &h()           { return _y; }
        unsigned &bpp()         { return _bpp; }
        bool     &fullscreen()  { return _fullscreen; }


    private:
        /* Физические данные, описание видеорежима */
        unsigned int _x;                    // Аппаратный используемый x
        unsigned int _y;                    // Аппаратный используемый y
        unsigned int _bpp;                  // Сколько бит на пиксел
        bool _fullscreen;                   // Во весь экран или окно?
};


// okay, let's left openGL only
// base screen class
class Screen
{
    public:
        Screen();
        ~Screen();

        void  setVideoMode(const VideoMode& mode);
        //const VideoMode getMaxVideoMode() const;     		  // получить максимально возможный видеорежим
        const VideoMode& getVideoMode() const;                    // get current videomode
        void  flipEntireScreen();                                 // entire buffer to real screen
        void  clearScreen(); 
        
        int   getMode();
        void  setMode(int);

        // vital
        void  putPixel (unsigned int x, unsigned int y, const Color & color);
        Color getPixel (unsigned int x, unsigned int y);

        // r they nec if we r using opengl ?
        void line(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const Color & color);  
        void rect(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const Color & color); 
        void bar(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const Color & color);

    private:
        std::vector <Color> buffer;         // virtual [emulated 320x2xx] screen
        static const int  virtualb;         // 320 px
        unsigned int      virtualw;         // it's width
        unsigned int      virtualh;         // and height
        unsigned int      virtuals;         // it's pixel size
        SDL_Surface      * context;         // SDL surface

        int                 sfmode;         // 0 - drawing to buffer, 1 - drawing to real screen with 1px pixel size
                                            // ^ game process only ^, ^^ rest of screens, settings etc.

        VideoMode currentMode;              // Информация о видеорежиме, используемом в данный момент
        bool hmax;                          // Используется ли max available videomode
        unsigned short fps;                 // Понты колотить :)
};

#endif

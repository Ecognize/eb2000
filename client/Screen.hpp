#ifndef _EB2K_SCREEN_HPP
#define _EB2K_SCREEN_HPP

#include <vector>
#include <iostream>

#include "SDL.h"
#include "Color.hpp"


class VideoMode
{
    public:
        VideoMode(int w,int h,int bpp=24,bool f=false, int p=1280) : _x(w),_y(h),_bpp(bpp),_fullscreen(f),_pitch(p) {  }

        unsigned w()          const { return _x; }
        unsigned h()          const { return _y; }
        unsigned bpp()        const { return _bpp; }
        unsigned pitch()      const { return _pitch; }
        bool     fullscreen() const { return _fullscreen; }

        unsigned &w()           { return _x; }
        unsigned &h()           { return _y; }
        unsigned &bpp()         { return _bpp; }
        unsigned &pitch()       { return _pitch; }
        bool     &fullscreen()  { return _fullscreen; }


    private:
        /* Физические данные, описание видеорежима */
        unsigned int _x;                    // Аппаратный используемый x
        unsigned int _y;                    // Аппаратный используемый y
        unsigned int _bpp;                  // Сколько бит на пиксел
        unsigned int _pitch;                // for SDL
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
        const VideoMode& getVideoMode() const; 
        void  flipEntireScreen();  // drawing gl_quads 
        void  clearScreen(); 
        
        void  putPixel (unsigned int x, unsigned int y, const Color & color);
        Color getPixel (unsigned int x, unsigned int y);

        void line(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const Color & color);  
        void rect(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const Color & color); 
        void bar(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const Color & color);
    private:
		// various OpenGL stuff

        VideoMode currentMode;              // Информация о видеорежиме, используемом в данный момент
        bool hmax;                          // Используется ли максимальное разрешение?
        unsigned short fps;                 // Понты колотить :)
};

#endif

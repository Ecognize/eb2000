#ifndef _EB2K_SCREEN_HPP
#define _EB2K_SCREEN_HPP

//#include <set>
//#include <utility>
#include <iostream>

#include "SDL.h"
#include "SDL/SDL_opengl.h"

#include "VideoMode.hpp"
#include "Color.hpp"

#define  FLIP_DIRECT   1
#define  FLIP_VIRTUAL  0


// okay, let's left openGL only
// base screen class
class Screen
{
    public:
        Screen();
        ~Screen();

        void  setVideoMode(const VideoMode& mode);
        //const VideoMode getMaxVideoMode() const;     		  // получить максимально возможный видеорежим

        const VideoMode& getCurrentMode() const; // get current screen dimensions depending on mode
        
        void  flipScreen();
        void  clearScreen(); 
        
        int   getMode();
        void  setMode(int);

        void  putPixel (unsigned int, unsigned int, const Color &);
        Color getPixel (unsigned int x, unsigned int y);

        void line(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const Color & color);  
        void rect(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const Color & color); 
        void bar(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const Color & color);

    private:
        void makeQuad(unsigned int, unsigned int, const Color &);
        
        static const unsigned int  vx;      // 312 px
        static const unsigned int  vy;      // 192 px
        unsigned int               ps;      // point size

        unsigned int xshift;
        unsigned int yshift;

        SDL_Surface      * context;         // SDL surface

        int                 sfmode;         // 0 - drawing to buffer, 1 - drawing to real screen with 1px pixel size
                                            // ^ game process only ^, ^^ rest of screens, settings etc.
        VideoMode currentMode;              // current hardware mode
        
        bool hmax;                          // Используется ли max available videomode
        unsigned short fps;                 // Понты колотить :)
};

#endif

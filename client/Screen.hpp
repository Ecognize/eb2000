#ifndef _EB2K_SCREEN_HPP
#define _EB2K_SCREEN_HPP

//#include <set>
//#include <utility>
#include <iostream>

#include "SDL.h"
#include "SDL/SDL_opengl.h"

#include "VideoMode.hpp"
#include "Color.hpp"
#include "Point.hpp"

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

        const VideoMode& getCurrentMode() const { return currentMode; }                  // get current videomode
        const VideoMode& getVirtualMode() const { return virtualMode; }
        
        void  flipEntireScreen();           // entire buffer to real screen
        void  flipScreen();
        void  clearScreen(); 
        
        int   getMode();
        void  setMode(int);

        // vital
        void  putPixel (const Point &, const Color &);
        void  putPixel (unsigned int, unsigned int, const Color &);
        
        Color getPixel (unsigned int x, unsigned int y);

        // r they nec if we r using opengl ?
        void line(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const Color & color);  
        void rect(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const Color & color); 
        void bar(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const Color & color);

    private:
        //typedef std::pair <Point, Color> TPoint;
        //typedef std::set  <TPoint> BType;
        
        static const int  virtualb;         // 320 px
        unsigned int         shift;         // if virtual screen does not match real ideally
        SDL_Surface      * context;         // SDL surface

        int                 sfmode;         // 0 - drawing to buffer, 1 - drawing to real screen with 1px pixel size
                                            // ^ game process only ^, ^^ rest of screens, settings etc.
        //BType buffer;       // all
        //BType matrix;       // new frame

        void makeQuad(const Point &, const Color &); 
        
        VideoMode currentMode;              // Информация о видеорежиме, используемом в данный момент
        VideoMode virtualMode;
        
        bool hmax;                          // Используется ли max available videomode
        unsigned short fps;                 // Понты колотить :)
};

#endif

#ifndef _EB2K_SCREEN_HPP
#define _EB2K_SCREEN_HPP

#include <vector>
#include <iostream>

#include "SDL.h"
#include "Color.h++"


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

// base template container for both rendering types
class Render
{
	public:
		Render();
		Render(enum renderType type);
		virtual ~Render();
		
        virtual void  setVideoMode(const VideoMode& mode);    // установить видеорежим
        //const VideoMode getMaxVideoMode() const;            // получить максимально возможный видеорежим
        virtual const VideoMode& getVideoMode() const;        // получить текущий видеорежим
        virtual void  flipEntireScreen();                     // перенести виртуальный буфер на экран
        virtual void  clearScreen();                          // очистить экран

        template <class ColorType> virtual void putPixel(unsigned int x, unsigned int y, const ColorType & color);                              // Поставить точку
        template <class ColorType> virtual ColorType getPixel(unsigned int x, unsigned int y);                                                 // Узнать цвет точки

        template <class ColorType> virtual void line(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const ColorType& color);  // Линия
        template <class ColorType> virtual void rect(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const ColorType& color);  // Рамка
        template <class ColorType> virtual void bar(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const ColorType& color);   // Закрашенный квадрат

	private:
		SDL_Surface * sdlSurface;    // physical screen
		std::vector <Color> buffer;  // screen buffer
		int vx;                      // his width
		int vy;                      // and height
		int psize;                   // size of physical point in px
		static const int _base;      // width of emulated screen (320 px)
};

// pure SDL software rendering
class SoftwareRender : public Render
{
	/* note: in this class we're forgiving about virtual buffer
	   and drawing directly on the SDL surface */
	   
	public:
 	    void  setVideoMode(const VideoMode& mode);
        //const VideoMode getMaxVideoMode() const;     		  // получить максимально возможный видеорежим
        const VideoMode& getVideoMode() const; 
        void  flipEntireScreen();  // SDL_UpdateRect will be here
        void  clearScreen(); 

		void putPixel(unsigned int x, unsigned int y, Uint32 & color);
		Uint32 getPixel (unsigned int x, unsigned int y);

        void line(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const Uint32 & color);  
        void rect(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const Uint32 & color); 
        void bar(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const Uint32 & color);
        
		// TODO: this stuff with pointers        
        // putpixel optimizations для разной глубины цвета (байтов на точку)
        void putpixel1(int, int, Uint32);
        void putpixel2(int, int, Uint32);
        void putpixel3(int, int, Uint32);
        void putpixel4(int, int, Uint32);
	private:
		int bpp; // bytes per pixel
};

// OpenGL hardware rendering (in SDL wrapper)
class HardwareRender : public Render
{
	// TODO: all
	/* note: in this class we're actively using virtual screen buffer, and
       communication with real screen happens only in flipEntireScreen()
       (for now).
    */
    	
 	public:
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
};

// base screen class
class Screen
{
    public:
        Screen();
        ~Screen();

		/* Graphics container and its type */
		Render render;
		enum renderType = {software, hardware};
		
    private:
        VideoMode currentMode;              // Информация о видеорежиме, используемом в данный момент
        bool hmax;                          // Используется ли максимальное разрешение?
        unsigned short fps;                 // Понты колотить :)
};

#endif

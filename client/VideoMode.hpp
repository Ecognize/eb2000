#ifndef __EB2K_VIDEOMODE_HPP
#define __EB2K_VIDEOMODE_HPP

// video mode container
class VideoMode
{
    public:
        VideoMode(int w,int h,int bpp=24,bool f=false) : _x(w),_y(h),_bpp(bpp),_fullscreen(f) {  }
        VideoMode() : _x(800), _y(600), _bpp(16), _fullscreen(false) { }
        
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


#endif
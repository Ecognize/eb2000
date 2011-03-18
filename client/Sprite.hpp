#ifndef _EB2K_SPRITE_HPP
#define _EB2K_SPRITE_HPP

#include <iostream>
#include <SDL.h>
#include <GL/gl.h>

class Sprite
{
    public:
        Sprite(std::string);
        ~Sprite();

        unsigned int x()      const { return _x; }
        unsigned int y()      const { return _y; }
        unsigned int zIndex() const { return _zIndex; }
        GLuint   name()       const { return _tname; }

        unsigned int xshift() const { return _xs; }
        unsigned int yshift() const { return _ys; }

        template <class T> T np2(T);

        unsigned int width()  const { return _spriteWidth; }
        unsigned int height() const { return _spriteHeight; }

        unsigned int &x()      { return _x; }
        unsigned int &y()      { return _y; }
        unsigned int &zIndex() { return _zIndex; }

    private:
        unsigned int _spriteWidth;
        unsigned int _spriteHeight;

        unsigned int _xs;
        unsigned int _ys;
        
        unsigned int _zIndex;   // layer in drawing
        unsigned int _x;        // sprite coords
        unsigned int _y;

        std::string  _tfile;    // texture file
        GLuint       _tname;    // GL texture name
        SDL_Surface * _surf;    // pointer to texture data
};

#endif

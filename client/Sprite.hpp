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

        unsigned int width()  const { return _spriteWidth; }
        unsigned int height() const { return _spriteHeight; }

        unsigned int &x()      { return _x; }
        unsigned int &y()      { return _y; }
        unsigned int &zIndex() { return _zIndex; }

    private:
        static const unsigned int _spriteWidth;
        static const unsigned int _spriteHeight;

        unsigned int _zIndex;   // layer in drawing
        unsigned int _x;        // sprite coords
        unsigned int _y;

        std::string  _tfile;    // texture file
        GLuint       _tname;    // GL texture name
        SDL_Surface * _surf;    // pointer to texture data
};

#endif

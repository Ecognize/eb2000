#ifndef _EB2K_SPRITE_HPP
#define _EB2K_SPRITE_HPP

#include <iostream>
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

        bool loadPNG(const char *);

        std::string  _tfile;    // texture file
        GLuint       _tname;    // GL texture name
        GLubyte    * _tdata;    // pointer to texture data
};

#endif

#ifndef _EB2K_SPRITE_CPP
#define _EB2K_SPRITE_CPP

#include <SDL_image.h>
#include "Sprite.hpp"

Sprite::Sprite(std::string file)
{
    _surf  = NULL;
    _tfile = file;
    _x = 0, _y = 0;
    _xs = 0, _ys = 0;

    // allocate a texture name
    glGenTextures( 1, &_tname );

    // select our current texture
    glBindTexture( GL_TEXTURE_2D, _tname );

    // read data from png
    _surf = IMG_Load(file.c_str());

    // store image size
    _spriteWidth = _surf->w;
    _spriteHeight = _surf->h;
	
	std::cout << "Sprite dimensions: " << _surf->w << "x" << _surf->h << std::endl;
	
    if(_surf != NULL)
    {
        std::string exts = std::string((const char *)glGetString(GL_EXTENSIONS));
        
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // if we not support np2-not-friendly textures
        if(1/*exts.find("ARB_texture_non_power_of_two") == std::string::npos*/)
        {
            // calculate canvas
			
            _xs = (np2(_surf->w) - _surf->w) / 2;
            _ys = (np2(_surf->h) - _surf->h) / 2;
			
			//_xs = (GLfloat)((_spriteWidth % 2 == 0) ? (_spriteWidth / 2) : _spriteWidth);
			//_ys = (GLfloat)((_spriteHeight % 2 == 0) ? (_spriteHeight / 2) : _spriteHeight);

            // expand texture
            /* expand _surf here */
			std::cout << "enlarged size is " << np2(_surf->w) << ", " << np2(_surf->h) << std::endl;
            std::cout << "texture shift is " << _xs << ", " << _ys << std::endl;
        }

		

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _surf->w, _surf->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, _surf->pixels); // assign data
        
        // disable texture filtering for pixel-precise sprites
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        // disable texture effects
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    }
    else std::cout << "can't read texture file" << std::endl;
}

Sprite::~Sprite()
{
    glDeleteTextures( 1, &_tname );
    SDL_FreeSurface(_surf);
    _surf = NULL;
}

// find closest power of two ABOVE specified value
template <class T> T Sprite::np2(T v)
{
    int k;
	T res;
	
    if (v == 0)
        return 1;

    for (k = sizeof(T) * 8 - 1; ((static_cast<T>(1U) << k) & v) == 0; k--);

    if (((static_cast<T>(1U) << (k - 1)) & v) == 0)
	{
		res = static_cast<T>(1U) << k;
		return ( res < v ) ? np2(v + (v / 2)) : res;
	}
	
	res = static_cast<T>(1U) << (k + 1);

    return (res < v) ? np2(v + (v / 2)) : res;
}

#endif

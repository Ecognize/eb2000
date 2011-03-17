#ifndef _EB2K_SPRITE_CPP
#define _EB2K_SPRITE_CPP

#include <SDL_image.h>
#include "Sprite.hpp"


const unsigned int Sprite::_spriteWidth  = 24;
const unsigned int Sprite::_spriteHeight = 24;

Sprite::Sprite(std::string file)
{
    _surf  = NULL;
    _tfile = file;
    _x = 0, _y = 0;

    // allocate a texture name
    glGenTextures( 1, &_tname );

    // select our current texture
    glBindTexture( GL_TEXTURE_2D, _tname );

    // read data from png
    _surf = IMG_Load(file.c_str());

    if(_surf != NULL)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _spriteWidth, _spriteHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, _surf->pixels); // assign data

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

#endif

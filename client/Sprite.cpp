#ifndef _EB2K_SPRITE_CPP
#define _EB2K_SPRITE_CPP

#include <png.h>
#include <cstdio>
#include <cstdlib>
#include "Sprite.hpp"


const unsigned int Sprite::_spriteWidth  = 24;
const unsigned int Sprite::_spriteHeight = 24;

Sprite::Sprite(std::string file)
{
    _tfile = file;
    _x = 0, _y = 0;

    // allocate a texture name
    glGenTextures( 1, &_tname );

    // select our current texture
    glBindTexture( GL_TEXTURE_2D, _tname );

    // read data from png
    if(loadPNG(const_cast<char *>(file.c_str())))
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _spriteWidth, _spriteHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, _tdata); // assign data

        glBlendFunc(GL_ONE, GL_ONE);

        // disable texture filtering for pixel-precise sprites
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        // disable texture effects
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);


    }
    else std::cout << "can't read texture file" << std::endl;
}

Sprite::~Sprite()
{
    glDeleteTextures( 1, &_tname );
}

bool Sprite::loadPNG(const char *name)
{
    png_structp png_ptr;
    png_infop info_ptr;
    unsigned int sig_read = 0;
    FILE *fp;

    if ((fp = fopen(name, "rb")) == NULL) return false;

    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (png_ptr == NULL) { fclose(fp); return false; }

    info_ptr = png_create_info_struct(png_ptr);

    if (info_ptr == NULL) { fclose(fp); png_destroy_read_struct(&png_ptr, NULL, NULL); return false; }

    if (setjmp(png_jmpbuf(png_ptr))) { png_destroy_read_struct(&png_ptr, &info_ptr, NULL); fclose(fp); return false; }

    png_init_io(png_ptr, fp);

    png_set_sig_bytes(png_ptr, sig_read);

    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);

    unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);

    _tdata = (unsigned char*) malloc(row_bytes * _spriteHeight);

    png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);

    for (int i = 0; i < _spriteHeight; i++)
        memcpy(_tdata + (row_bytes * i), row_pointers[i], row_bytes);

    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

    fclose(fp);

    return true;
}

#endif

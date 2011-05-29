#include "client/Screen.hpp"
#include <cstdio>
#include <cstdlib>
#include <cmath>

int main(int argc, char *argv[])
{
    bool fullscreen = true;
	
    if (argc == 2 && strcmp(argv[1],"-f"))
       fullscreen = false;

    // init SDL
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Event event;

    Screen screen;
    screen.setVideoMode(screen.getMaxVideoMode());

    int w = screen.width();
    int h = screen.height();

    bool done = false;

    Sprite sprite("test.png");

    screen.putSprite((w + sprite.width()) / 2, (h  + sprite.height()) / 2, sprite);

    screen.flipScreen();

    while(!done)
    {
        while ( SDL_PollEvent(&event) )
        {
            if ( (event.type == SDL_KEYDOWN) || (event.type == SDL_QUIT) )
              done = 1;
        }
    }

//SDL_Quit();
    return 0;
}


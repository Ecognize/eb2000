#include "client/Screen.hpp"
#include <cstdio>
#include <cstdlib>
#include <cmath>

int main()
{
    Screen screen;

    int sw = 800;
    int sh = 600;

    // init SDL
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Event event;

    screen.setVideoMode(VideoMode(sw,sh,32,false));

    // set direct drawing
    //screen.setMode(FLIP_VIRTUAL); // or try FLIP_VIRTUAL

    // fetch current screen dims
    VideoMode vmode = screen.getCurrentMode();

    int w = screen.width();
    int h = screen.height();

    bool done = false;

    Sprite sprite("test.png");

    screen.putSprite(w / 2, h / 2, sprite);

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


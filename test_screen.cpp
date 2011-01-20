#include "client/Screen.hpp"
#include <cstdio>
#include <cstdlib>
#include <cmath>

int main()
{
    Screen screen;

    int w = 320;
    int h = 200;

    // init SDL
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Event event;

    screen.setVideoMode(VideoMode(w,h,32,false));

    bool done = false;

    while(!done)
    {
        screen.line(random() % w, random() % h, random() % w, random() % h, Color::Yellow);
        screen.line(random() % w, random() % h, random() % w, random() % h, Color::Red);
        screen.line(random() % w, random() % h, random() % w, random() % h, Color::Green);
        screen.line(random() % w, random() % h, random() % w, random() % h, Color::Blue);
        screen.line(random() % w, random() % h, random() % w, random() % h, Color::White);
        screen.flipEntireScreen();

        while ( SDL_PollEvent(&event) )
        {
            if ( (event.type == SDL_KEYDOWN) || (event.type == SDL_QUIT) )
              done = 1;
        }
    }
    //SDL_Quit();
    return 0;
}

#include "client/Screen.hpp"
#include <cstdio>
#include <cstdlib>
#include <cmath>

int main(int argc, char *argv[])
{
    bool fullscreen = true;
	
    if (argc == 2 && strcmp(argv[1],"-f"))
       fullscreen = false;

    Screen screen;

    int sw = 1024;
    int sh = 768;

    // init SDL
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Event event;

    screen.setVideoMode(VideoMode(sw,sh,32,fullscreen));

    // set direct drawing
    screen.setMode(FLIP_VIRTUAL); // or try FLIP_VIRTUAL

    int w = screen.width();
    int h = screen.height();
    
    bool done = false;

    Uint32 fps_lasttime = SDL_GetTicks(); //the last recorded time.
    Uint32 fps_current = 0; //the current FPS.
    Uint32 fps_frames = 0; //frames passed since the last recorded fps.

    while(!done)
    {
        screen.line(random() % w, random() % h, random() % w, random() % h, Color::Yellow);
        screen.line(random() % w, random() % h, random() % w, random() % h, Color::Red);
        screen.line(random() % w, random() % h, random() % w, random() % h, Color::Green);
        screen.line(random() % w, random() % h, random() % w, random() % h, Color::Blue);
        screen.line(random() % w, random() % h, random() % w, random() % h, Color::White);
        screen.flipScreen();

        fps_frames++;

        if (fps_lasttime < SDL_GetTicks() - 1000)
        {
           fps_lasttime = SDL_GetTicks();
           fps_current = fps_frames;
           fps_frames = 0;

           std::cout << "FPS: " << fps_current << std::endl;
        }

        while ( SDL_PollEvent(&event) )
        {
            if ( (event.type == SDL_KEYDOWN) || (event.type == SDL_QUIT) )
              done = 1;
        }
    }
    //SDL_Quit();
    return 0;
}

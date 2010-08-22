#include "client/Screen.h++"
#include <cstdlib>
#include <cmath>

void kbhit()
{
        SDL_Event event;
        int status;
        int quit = 0;
        while ( !quit )
        {
                status = SDL_WaitEvent(&event);
                switch (event.type)
                {
                        case SDL_KEYDOWN:
                        quit = 1;
                        break;
                }
        }
}

void drawPlasma(int,int,Screen);

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    int width = 800;
    int height = 600;
    
    Screen screen;
    screen.setVideoMode(VideoMode(width,height,16));
                                        //^^^ 32 here causes SEGFAULT during _putpixel :(
    screen.setScaling();

    SDL_Event event;
    unsigned int FPS;
    int start, delta;

    start = SDL_GetTicks();

    while (1)
    {
        // FPS calculating
        delta = SDL_GetTicks() - start;
        start = SDL_GetTicks();

        if ( delta != 0 )
            FPS = 1000 / delta;

        std::cout << "FPS: " << FPS << std::endl;

        screen.line(height / 2, width / 2, rand() % width / 2 , rand() % height / 3, Color::Green);

        // two huge bottlenecks
        screen.flipScreen();
        screen.clearScreen();

        // handling the ESC
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_KEYDOWN:
                break;
                case SDL_KEYUP:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    return 0;
                break;
                case SDL_QUIT:
                return(0);
            }
        }
    }
    //SDL_Quit();
    return 0;
}

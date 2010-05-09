#include "client/Screen.h++"

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

int main()
{
    SDL_Init(SDL_INIT_VIDEO);


    Screen screen;

    screen.setVideoMode(VideoMode(800,600,32));

    screen.setScaling();

    screen.line(0,0,200,300,Color::Blue);

    screen.flipScreen();

    kbhit();

    SDL_Quit();
    return 0;
}
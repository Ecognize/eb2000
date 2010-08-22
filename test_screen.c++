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

    screen.setVideoMode(VideoMode(800,600,16));

    screen.setScaling();
int i =0 ;
   while (1)
  {
    // Render stuff
    screen.line(0,0,i,300,Color::Red);


    screen.flipScreen();
    i++;
    if(i >= 800) i =0;

    // Poll for events, and handle the ones we care about.
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_KEYDOWN:
        break;
      case SDL_KEYUP:
        // If escape is pressed, return (and thus, quit)
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
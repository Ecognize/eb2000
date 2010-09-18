#include "client/Screen.h++"
#include <cstdio>
#include <cstdlib>
#include <cmath>

static Uint32 colors[256];
static int xoff, yoff;

static double angle = 0.0;

static int frames = 0;

static int stars[100][3];
static int starsr[100][3];
static int old[100][3];

void Transform(int *ta, int *tb)
{
    double y = 0.0, z = 0.0;
    y = (cos((angle / 20)) * *ta) - (sin((angle / 20)) * *tb);
    z = (sin((angle / 20)) * *ta) + (cos((angle / 20)) * *tb);
    *ta = (int) floor(y);
    *tb = (int) floor(z);
}

void InitStars(SDL_Surface * video)
{
    int i;
    srand(time(NULL));
    for (i = 0; i < 100; i++)
    {
        stars[i][0] = ((rand() % 320)+1 - 160) * 3;
        stars[i][1] = ((rand() % 320)+1 - 160) * 3;
        stars[i][2] = ((rand() % 128)+1 - 64) * 5;
    }

        /* Assuming 8-bit palette */
    if ( video->format->palette ) {
        SDL_Color clut[256];

        for (i = 0; i < 256; i++) {
            clut[i].r = i;
            clut[i].g = i;
            clut[i].b = i;
        }
        SDL_SetColors(video, clut, 0, 256);
    }
    for (i = 0; i < 256; i++) {
        colors[i] = SDL_MapRGB(video->format, i, i, i);
    }

        /* We ignore all but keyboard events */
    for ( i = 0; i<SDL_NUMEVENTS; ++i ) {
        if ( (i != SDL_KEYDOWN) && (i != SDL_QUIT) ) {
            SDL_EventState(i, SDL_IGNORE);
        }
    }
}


int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    int width = 640;
    int height = 480;
    int xoff = width / 2, yoff = height / 2;
    int i;
    int x, y, oldx, oldy;
    double fps = 0.0;
    time_t st, lap;
    Uint8 color = 0;

    Screen screen;
    screen.setVideoMode(VideoMode(width,height,32));

    SDL_Surface * p = screen.getSurface();
    
    printf("pitch == %d, bbp == %d\n", p->pitch, p->format->BytesPerPixel);
    screen.setScaling();

    InitStars(screen.getSurface());
    st = time(NULL);
    lap = st;
    
    do  {
        for (i = 0; i < 100; i++)
        {
            old[i][0] = starsr[i][0];
            old[i][1] = starsr[i][1];
            old[i][2] = starsr[i][2];

            starsr[i][0] = stars[i][0];
            starsr[i][1] = stars[i][1];
            starsr[i][2] = stars[i][2];

            Transform(&starsr[i][1], &starsr[i][2]);
            Transform(&starsr[i][0], &starsr[i][2]);
            Transform(&starsr[i][0], &starsr[i][1]);

            oldx = (int) floor(((256*old[i][0])/(old[i][2]-1024))+xoff);
            oldy = (int) floor(((256*old[i][1])/(old[i][2]-1024))+yoff);

            x = (int) floor(((256*starsr[i][0])/(starsr[i][2]-1024))+xoff);
            y = (int) floor(((256*starsr[i][1])/(starsr[i][2]-1024))+yoff);

            color = floor((starsr[i][2] + 721) / 5.5);
            
            screen.putPixel(oldx, oldy, colors[0]);
            screen.putPixel(x, y, colors[color]);
        }
        screen.flipScreen();
        frames++;
        angle += 0.5;
        
    } while( SDL_PollEvent(NULL) == 0);

    if ((time(NULL) - st) != 0)
        fps = (double)frames / (time(NULL) - st);
    printf("%2.2f frames per second\n", fps);    
    printf("beek / lightspeed\n\nPorted to GGI by Nathan Strong\n");
    printf("Ported to SDL by Sam Lantinga\n");
    
    
    return 0;
}

#include "SDL.h" 
#include <math.h> 
#include <stdio.h> 
#include <stdlib.h> 

// uncomment to compile
// #include "AbstractScene.h"
// #include "Actor.h"

class Graph
{
    public:
    Graph(int,int,int);
    ~Graph();

    void init();                        // set videomode
    void putpixel(int,int,Uint32);      // pixel
    void line(int,int,int,int,Uint32);  // line

    Uint32 RGB(Uint8,Uint8,Uint8);      // rgb to uint32

    private:
    SDL_Surface * s;                    // screen
    int w, h, b;                        // width, height, bpp
};

Graph::Graph(int x,int y,int p)
{
    SDL_Init(SDL_INIT_VIDEO);

    w = x;
    h = y;
    b = p;
}

Graph::~Graph()
{
    SDL_Quit();
}

Uint32 Graph::RGB(Uint8 r, Uint8 g, Uint8 b)
{
    return SDL_MapRGB(s->format, r, g, b);
}

void Graph::init()
{
    s = SDL_SetVideoMode( w, h, b, SDL_HWSURFACE);

    if ( s == NULL )
    {
        fprintf(stderr, "failed. (%s)\n", SDL_GetError());
        exit(1);
    }
}

void Graph::putpixel(int x, int y, Uint32 pixel)
{
    int z = s->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)s->pixels + y * s->pitch + x * z; 

    switch(z)
    { 
        case 1: 
        *p = pixel; 
        break; 

        case 2: 
        *(Uint16 *)p = pixel; 
        break; 

        case 3: 
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN) { 
                p[0] = (pixel >> 16) & 0xff; 
                p[1] = (pixel >> 8) & 0xff; 
                p[2] = pixel & 0xff; 
            } else { 
                p[0] = pixel & 0xff; 
                p[1] = (pixel >> 8) & 0xff; 
                p[2] = (pixel >> 16) & 0xff; 
            } 
        break; 

        case 4: 
        *(Uint32 *)p = pixel; 
        break; 
    } 
}

void Graph::line(int x0, int y0, int x1, int y1, Uint32 color)
{
    int dy = y1 - y0;
    int dx = x1 - x0;
    int stepx, stepy;
    int fraction;

    if (dy < 0) { dy = -dy;  stepy = -1; } else { stepy = 1; }
    if (dx < 0) { dx = -dx;  stepx = -1; } else { stepx = 1; }

    dy <<= 1;              // dy == 2*dy
    dx <<= 1;              // dx == 2*dx

    putpixel(x0, y0, color);

    if (dx > dy)
    {
        fraction = dy - (dx >> 1);                         // == 2*dy - dx
        while (x0 != x1)
        {
            if (fraction >= 0)
            {
                y0 += stepy;
                fraction -= dx;
            }
            x0 += stepx;
            fraction += dy;
            putpixel(x0, y0, color);
        }
    } else {
        fraction = dx - (dy >> 1);
        while (y0 != y1)
        {
            if (fraction >= 0)
            {
                x0 += stepx;
                fraction -= dy;
            }
            y0 += stepy;
            fraction += dx;
            putpixel(x0, y0, color);
        }
    }
}

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
        Graph scr(800, 600, 32);

        scr.init();

        /*if (SDL_MUSTLOCK(display)) 
                if (SDL_LockSurface(display) < 0) 
                        exit(1); 
        for(yf=0;yf<vmaxy;yf++) 
                for(xf=0;xf<vmaxx;xf++) 
                { 
                        //1 virtual pixel 
                        for(i=0;i<ar;i++) 
                                for(j=0;j<ar;j++) 
                                { 
                                        putpixel(display,xf*ar+i,yf*ar+j,SDL_MapRGB(display->format, 
vscreen[xf][yf].r, vscreen[xf][yf].g, vscreen[xf][yf].b )); 
                                } 
                }                       
        if (SDL_MUSTLOCK(display)) 
                SDL_UnlockSurface(display); 
        SDL_Flip(display); 
        //****************** 
        kbhit(); 
        SDL_Quit(); 
        */
        
        /* Main loop logic */
        /*
        
        SomeSceneClass scene;
        while (not need to quit)
        {
            scene.recieveMessages();
            drawWalls() -- пока забей
            for (AbstractScene::iterator i=scene.begin();i!=scene.end();end())
            {
                Actor &act=(*i);
                int x=act.position().x()*SCREEN_WIDTH;
                int y=act.position().y()*SCREEN_HEIGHT; // TODO
                int halfwidth=act.class().width()/2;
                int halfwidth=act.class().height()/2;
                Color col=colors[act.class().id()];
                drawRectangle(x-halfwidth,y-halfheight,x+halfwidth,y+halfheight,col);
            }
        }
        
        
        */
        
        
        for(int i = 0; i < 128; i++)
            scr.line(rand() % 800, rand() % 600, rand() % 800, rand() % 600, scr.RGB(0,i,0));

        kbhit();
        return 0; 
} 
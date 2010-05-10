#include "../client/Screen.h++"
#include "../shared/AbstractScene.h++"
#include "../shared/Actor.h++"

bool quit()
{
    SDL_Event event;
    int status = SDL_WaitEvent(&event);

    if(event.type == SDL_KEYDOWN)
        return 1;
    else return 0;
}

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    Screen screen;
    screen.setVideoMode(VideoMode(800,600,32));
    screen.setScaling();

    int x, y, halfwidth, halfheight;

    /* Main loop logic */
    SomeSceneClass scene;
    while (!quit())
    {
        scene.receiveMessages();
        //drawWalls() -- пока забей

        for (AbstractScene::iterator i = scene.begin(); i != scene.end(); end())
        {
            Actor &act = (*i);
            x = act.position().x() * SCREEN_WIDTH;
            y = act.position().y() * SCREEN_HEIGHT; // TODO
            halfwidth  = act.class().width()  / 2;
            halfheight = act.class().height() / 2;
            Color col = colors[act.class().id()];
            screen.bar(x - halfwidth, y - halfheight, x + halfwidth, y + halfheight, col);
        }
        screen.flipScreen();
    }
    SDL_Quit();
} 
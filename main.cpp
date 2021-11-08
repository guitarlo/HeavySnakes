#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "menu.h"
#include "game.h"
#include "snowgame.h"

#include "sblogo.h"
using namespace std;
SDL_Window *wnd;
SDL_Renderer *rnd;
int _screenW=640, _screenH=480;
int init();
int main(int argc, char *argv[])
{

    init();
    SDL_ShowCursor(SDL_FALSE);
    sbLogo logo(rnd);
    logo.run();
    Menu menu(rnd,&_screenW,&_screenH);
    menu.showMenu();
    //game g(rnd,1,&_screenW,&_screenH);
    //g.run();
    cout << "Everythings fine";
    SDL_ShowCursor(SDL_FALSE);
    IMG_Quit();
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
    return 0;
}


int init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING)==-1)
        cout << "Fehler bei der initialisierung!"<<endl;

    Mix_OpenAudio(44100,AUDIO_S16,2,2048);
    if (TTF_Init() == -1)
    {
        cout << "SDL_ttf could not initialize!" << endl;

    }
    Mix_AllocateChannels(24);
    SDL_Rect t;
    SDL_GetDisplayBounds(0,&t);

    _screenW=t.w;
    _screenH=t.h;
    wnd=SDL_CreateWindow("Heavy Snakes",0,0,_screenW,_screenH,SDL_WINDOW_FULLSCREEN);
    if (wnd==NULL)
        return -1;
    rnd=SDL_CreateRenderer(wnd,-1,SDL_RENDERER_ACCELERATED);
    if (rnd==NULL)
        return -1;


    return 0;
}

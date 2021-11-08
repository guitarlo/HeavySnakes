#ifndef MENU_H
#define MENU_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "sprite.h"
#include "cfnt.h"
#include "game.h"
#include "snowgame.h"
class Menu
{
public:
    Menu(SDL_Renderer *rnd,int *screenW, int *screenH);
    int showMenu();
private:
    SDL_Renderer *_rnd;
    SDL_Event e;
    SDL_Joystick *js;
    int *_screenW, *_screenH;
    bool _run;
};

#endif // MENU_H

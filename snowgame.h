#ifndef SNOWGAME_H
#define SNOWGAME_H
#include <sstream>
#include <vector>
#include "sprite.h"
#include "icelevel.h"
#include "snake.h"
#include "collision.h"
#include "crobby.h"
#include "cfnt.h"
#include "cbombs.h"
#include "ctimer.h"
class snowGame
{
public:
    snowGame(SDL_Renderer *rnd, int player, int *screenW, int *screenH);
    void run();

private:
    SDL_Renderer *_rnd;
    SDL_Joystick *js1,*js2;
    SDL_Haptic *jsh1,*jsh2;
    SDL_Event e;
    int _tileSize=64,m_scale=0,m_eat_snd=0;
    int m_Player=0,m_dir=0,m_dir2=0,startState=0;
    bool _run;
    int m_screenW=0, m_screenH=0,message=0;
    cbombs *tempBomb;
    vector <cbombs> bomblist;
};

#endif // SNOWGAME_H

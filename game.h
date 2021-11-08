#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL_mixer.h>
#include <time.h>
#include <vector>
#include "sprite.h"
#include "snake.h"
#include "cfnt.h"
#include "clevel.h"
#include "collision.h"
#include "orb.h"
#include "cbombs.h"
using namespace std;
class game
{
public:
    game(SDL_Renderer *rnd,int player, int *screenW , int *screenH);
    void run();
private:
    SDL_Renderer *_rnd;
    SDL_Joystick *js1,*js2;
    SDL_Haptic *jsh1,*jsh2;
    SDL_Event e;
    int _tileSize=64,m_scale=0,m_eat_snd=0;
    int m_Player=0,m_dir=0,m_dir2=2,startState=0;
    bool _run;
    int m_screenW=0, m_screenH=0;
    cbombs *tempBomb;
    vector<cbombs> bomblist;

};

#endif // GAME_H

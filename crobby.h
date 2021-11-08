#ifndef CROBBY_H
#define CROBBY_H

#include <time.h>
#include "sprite.h"
#include <SDL2/SDL_mixer.h>
class crobby
{
public:
    crobby(SDL_Renderer *rnd, int *screenW, int *screenH,int *tileSize);
    void spawn();
    int getX();
    int getY();
    void draw(int good_or_bad);
private:
    int *m_screenW,*m_screenH, *m_tileSize, m_x,m_y;
    SDL_Renderer *_rnd;
    sprite *s_robby,*s_robby_dance,*s_robby_bad,*s_robby_dance_bad;
    int m_robby_state=0, m_bad_or_good=0;

    Mix_Chunk *snd_hurra;

};

#endif // ORB_H

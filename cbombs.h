#ifndef CBOMBS_H
#define CBOMBS_H
#include<SDL2/SDL_mixer.h>
#include "sprite.h"
#include "collision.h"
#include "snake.h"
class cbombs
{
public:
    cbombs(SDL_Renderer *rnd,int x, int y, int *size);
    void update(snake *snake);
    void setX(int X);
    void setY (int Y);
    void setDead (bool dead);
    bool getDead();

private:
    collision _collision;
    int m_x=0,m_y=0, m_size=0,state=0;
    Uint32 m_offset=0,curTime=0;
    sprite *s_segment,*s_explosion,*s_explosion2;
    bool m_dead=false;
    Mix_Chunk *snd_splat;
};

#endif // CBOMBS_H

#ifndef ORB_H
#define ORB_H
#include <time.h>
#include "sprite.h"

class orb
{
public:
    orb(SDL_Renderer *rnd, int *screenW, int *screenH,int *tileSize);
    void spawn();
    int getX();
    int getY();
    void draw();
private:
    int *m_screenW,*m_screenH, *m_tileSize, m_x,m_y;
    SDL_Renderer *_rnd;
    sprite *s_orb;

};

#endif // ORB_H

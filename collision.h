#ifndef COLLISION_H
#define COLLISION_H
#include<SDL2/SDL.h>

class collision
{
public:
    collision();
    int rect(SDL_Rect r1,SDL_Rect r2);
    int offset=15;
};

#endif // COLLISION_H

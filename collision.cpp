#include "collision.h"

collision::collision()
{

}
int collision::rect(SDL_Rect r1,SDL_Rect r2)
{
    if(r1.x+r1.w+offset > r2.x+offset &&
       r1.x-offset < r2.x+r2.w-offset &&
       r1.y+r1.h+offset > r2.y+offset &&
       r1.y-offset < r2.y+r2.h-offset)
        return 1;
    return 0;
}

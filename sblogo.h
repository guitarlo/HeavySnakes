#ifndef SBLOGO_H
#define SBLOGO_H
#include "sprite.h"
#include <SDL2/SDL_mixer.h>

class sbLogo
{
public:
    sbLogo(SDL_Renderer *rnd);
    void run();
private:
    SDL_Renderer *_rnd;
    SDL_Rect r_white;
    bool m_run=true;
    SDL_Event e;
    float m_alpha=0;
    int state=0;
};

#endif // SBLOGO_H

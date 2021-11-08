#include "sblogo.h"

sbLogo::sbLogo(SDL_Renderer* rnd)
{
    _rnd =rnd;
}

void sbLogo::run()
{
    sprite s_logo (_rnd,"GFX/Logo.png");
    SDL_Rect r;
    SDL_GetDisplayBounds(0,&r);

    s_logo.setXY((r.w/2)-512,(r.h/2)-382);
    s_logo.setAlpha(0);
    Mix_Chunk *snd_Logo=Mix_LoadWAV("SND/Scorebox_melo.wav");
    Mix_VolumeChunk(snd_Logo,20);
    Uint32 startTimer,delayTimer;

    while (m_run)
    {
        startTimer=SDL_GetTicks();
        SDL_SetRenderDrawColor(_rnd,255,255,255,255);
        SDL_RenderClear(_rnd);
        s_logo.draw();

        SDL_RenderPresent(_rnd);
        while(SDL_PollEvent(&e))
        {
            if (e.type==SDL_KEYDOWN)
            {
                if(e.key.keysym.sym==SDLK_ESCAPE)
                    m_run=false;
            }

        }
        if (state==0)
        {
            if (m_alpha<255)
            {
                m_alpha+=1;
                s_logo.setAlpha(m_alpha);
            }
            if (m_alpha==255)
            {
                state=1;
                Mix_PlayChannel(0,snd_Logo,0);
            }

        }
        if (state==1)
        {
            if (m_alpha>0)
            {
                m_alpha-=1;
                s_logo.setAlpha(m_alpha);
            }
            if (m_alpha==0 and Mix_Playing(0)==0)
                m_run=false;
        }

        delayTimer=SDL_GetTicks()-startTimer;
       if(delayTimer < 1000/60)
       SDL_Delay((1000/60)-delayTimer);

    }
}

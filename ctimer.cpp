#include "ctimer.h"

ctimer::ctimer()
{
    m_offset=SDL_GetTicks();
}
Uint32 ctimer::getTime(){return SDL_GetTicks()-m_offset;}
void ctimer::reset(){m_offset=SDL_GetTicks();}

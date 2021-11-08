#ifndef CTIMER_H
#define CTIMER_H
#include <SDL2/SDL.h>

class ctimer
{
public:
    ctimer();
    Uint32 getTime();
    void reset();
private:
int m_offset;
};

#endif // CTIMER_H

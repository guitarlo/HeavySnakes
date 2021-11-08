#include "cbombs.h"

cbombs::cbombs(SDL_Renderer *rnd, int x, int y, int *size)
{
    m_x=x;
    m_y=y;
    m_size= *size;
    s_segment=new sprite(rnd,"GFX/Snake_body.png");
    s_segment->createFrame(15,1);
    s_segment->setXY(m_x,m_y);
    s_explosion=new sprite(rnd,"GFX/Snake_body_splat.png");
    s_explosion->createFrame(11,1);
    s_explosion2=new sprite(rnd,"GFX/Blood.png");
    s_explosion2->createFrame(70,1);

    m_offset=SDL_GetTicks();
    snd_splat=Mix_LoadWAV("SND/Splat.wav");


}
void cbombs::update(snake *snake)
{
    curTime=SDL_GetTicks()-m_offset;

    if (_collision.rect({snake->getX(),snake->getY(),m_size,m_size},{m_x,m_y,m_size,m_size})==1)
        snake->setDead(true);
    if (state==0)
    {
        if ((curTime/1000)>=3)
        {

            state=1;
            s_explosion->resetOneShot();
            Mix_PlayChannel(-1,snd_splat,0);

        }
        s_segment->setXY(m_x,m_y);
        s_segment->drawFrames(0);
    }

    if (state==1)
    {

        s_explosion->setXY(m_x,m_y);
        s_explosion->drawOneShot(0);
        s_explosion2->setXY(m_x+m_size,m_y);
        s_explosion2->drawOneShot(0);
        s_explosion2->setXY(m_x-m_size,m_y);
        s_explosion2->drawOneShot(0);
        s_explosion2->setXY(m_x,m_y+m_size);
        s_explosion2->drawOneShot(0);
        s_explosion2->setXY(m_x,m_y-m_size);
        s_explosion2->drawOneShot(0);

        if (_collision.rect({snake->getX(),snake->getY(),m_size,m_size},{m_x,m_y,m_size,m_size})==1)
            snake->setDead(true);
        if (_collision.rect({snake->getX(),snake->getY(),m_size,m_size},{m_x+m_size,m_y,m_size,m_size})==1)
            snake->setDead(true);
        if (_collision.rect({snake->getX(),snake->getY(),m_size,m_size},{m_x+m_size,m_y,m_size,m_size})==1)
            snake->setDead(true);
        if (_collision.rect({snake->getX(),snake->getY(),m_size,m_size},{m_x,m_y-m_size,m_size,m_size})==1)
            snake->setDead(true);
        if (_collision.rect({snake->getX(),snake->getY(),m_size,m_size},{m_x,m_y+m_size,m_size,m_size})==1)
            snake->setDead(true);
        if(s_explosion->getCurrentFrame()==s_explosion->getMaxFrames()-1)
            m_dead=true;
    }

}
void cbombs::setX(int X)
{
    m_x=X;
}
void cbombs::setY (int Y)
{
    m_y=Y;}
void cbombs::setDead(bool dead)
{
    m_dead=dead;
}
bool cbombs::getDead()
{
    return m_dead;
}

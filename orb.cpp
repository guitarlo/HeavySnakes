#include "orb.h"

orb::orb(SDL_Renderer *rnd, int *screenW, int *screenH,int *tileSize)
{
    m_screenW=screenW;
    m_screenH=screenH;
    _rnd=rnd;
    m_tileSize=tileSize;
    s_orb=new sprite(_rnd,"GFX/Orb.png");
    s_orb->createFrame(9,1);

}
void orb::spawn()
{


    m_x=rand()%*m_screenW-*m_tileSize;
    m_y=rand()%*m_screenH-*m_tileSize;

    s_orb->setXY(m_x,m_y);

}
int orb::getX(){return m_x;}
int orb::getY(){return m_y;}
void orb::draw()
{
    s_orb->drawFrames(0);
}

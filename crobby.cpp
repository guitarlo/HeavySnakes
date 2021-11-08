#include "crobby.h"



crobby::crobby(SDL_Renderer *rnd, int *screenW, int *screenH,int *tileSize)
{
    m_screenW=screenW;
    m_screenH=screenH;
    _rnd=rnd;
    m_tileSize=tileSize;
    s_robby=new sprite(_rnd,"GFX/Robby_break.png");
    s_robby->createFrame(21,1);
    s_robby_dance=new sprite(_rnd,"GFX/Robby_dance.png");
    s_robby_dance->createFrame(5,1);


    s_robby_bad=new sprite(_rnd,"GFX/Robby_break_bad.png");
    s_robby_bad->createFrame(21,1);
    s_robby_dance_bad=new sprite(_rnd,"GFX/Robby_dance_bad.png");
    s_robby_dance_bad->createFrame(5,1);

    snd_hurra= Mix_LoadWAV("SND/Hurra.wav");
}
void crobby::spawn()
{


    m_x=rand()%*m_screenW-*m_tileSize;
    m_y=rand()%*m_screenH-*m_tileSize;

    s_robby->setXY(m_x,m_y);    
    s_robby_dance->setXY(m_x,m_y);
    s_robby_bad->setXY(m_x,m_y);
    s_robby_dance_bad->setXY(m_x,m_y);

    m_robby_state=0;
    cout << "ORB X: "<< m_x <<", Y: "<<m_y<<endl;
}
int crobby::getX(){return m_x;}
int crobby::getY(){return m_y;}
void crobby::draw(int bad_or_good)
{
    m_bad_or_good=bad_or_good;
    if (bad_or_good<3)
    {
        if (m_robby_state==0)
        {
            s_robby->resetOneShot();
            s_robby_dance->resetOneShot();
            m_robby_state=1;
        }
        if (m_robby_state==1)
        {
            s_robby->drawOneShot(0);
            if (s_robby->getCurrentFrame()==s_robby->getMaxFrames()-1)
                m_robby_state=2;
            if (s_robby->getCurrentFrame()==13)
                if(Mix_Playing(5)==0)
                    Mix_PlayChannel(5, snd_hurra,0);
        }
        if(m_robby_state==2)
            s_robby_dance->drawFrames(0);

    }
    else
    {
        if (m_robby_state==0)
        {
            s_robby_bad->resetOneShot();
            s_robby_dance_bad->resetOneShot();
            m_robby_state=1;
        }
        if (m_robby_state==1)
        {
            s_robby_bad->drawOneShot(0);
            if (s_robby_bad->getCurrentFrame()==s_robby->getMaxFrames()-1)
                m_robby_state=2;
            if (s_robby_bad->getCurrentFrame()==13)
                if(Mix_Playing(5)==0)
                    Mix_PlayChannel(5, snd_hurra,0);
        }
        if(m_robby_state==2)
            s_robby_dance_bad->drawFrames(0);
    }

}

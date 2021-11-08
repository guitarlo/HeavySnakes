#include "snake.h"

snake::snake(SDL_Renderer *rnd, int player)
{
    _rnd=rnd;
    if(player==1)
    {
        s_animation[0]=new sprite(_rnd, "GFX/Snake_Side.png");
        s_animation[0]->createFrame(13,1);

        s_animation[1]=new sprite(_rnd, "GFX/Snake_down.png");
        s_animation[1]->createFrame(13,1);

        s_animation[2]=new sprite(_rnd, "GFX/Snake_Side.png");
        s_animation[2]->createFrame(13,1);

        s_animation[3]=new sprite(_rnd, "GFX/Snake_up.png");
        s_animation[3]->createFrame(13,1);

        s_splat=new sprite(_rnd,"GFX/Snake_body_splat.png");
        s_splat->createFrame(11,1);
        s_segment = new sprite(_rnd,"GFX/Snake_body.png");
        s_segment->createFrame(15,1);

        s_segment->setScale(-15);
        snd_kriech1=Mix_LoadWAV("SND/kriech1.wav");
        snd_kriech2=Mix_LoadWAV("SND/kriech2.wav");
        snd_kriech3=Mix_LoadWAV("SND/kriech3.wav");
        snd_kriech4=Mix_LoadWAV("SND/kriech4.wav");


    }
    m_player=player;
    if(player==2)
    {
        s_animation[0]=new sprite(_rnd, "GFX/Snake2_Side.png");
        s_animation[0]->createFrame(13,1);

        s_animation[1]=new sprite(_rnd, "GFX/Snake2_down.png");
        s_animation[1]->createFrame(13,1);

        s_animation[2]=new sprite(_rnd, "GFX/Snake2_Side.png");
        s_animation[2]->createFrame(13,1);

        s_animation[3]=new sprite(_rnd, "GFX/Snake2_up.png");
        s_animation[3]->createFrame(13,1);

        s_splat=new sprite(_rnd,"GFX/Snake2_body_splat.png");
        s_splat->createFrame(11,1);
        s_segment = new sprite(_rnd,"GFX/Snake2_body.png");
        s_segment->createFrame(15,1);

        s_segment->setScale(-15);
    }

    snd_splat= Mix_LoadWAV("SND/Splat.wav");

}
snake::~snake()
{
    delete s_segment;
    delete s_splat;
    for (int i=0 ; i<3; i++)
        delete s_animation[i];
}

void snake::draw(int animation)
{
    segment *seg;
    if(!m_dead)
    {
        m_dead=0;
        s_splat->resetOneShot();
        s_animation[animation]->setXY(m_x,m_y);
        if (animation==2)
            s_animation[animation]->drawFrames(true);
        else
            s_animation[animation]->drawFrames(false);

        for(int i=0;i < int(segmentList.size());i++)
        {
            seg=&segmentList[i];
            s_segment->setXY(seg->getX(),seg->getY());
            s_segment->drawFrames(0);
        }
    }
    else {
        s_splat->setXY(m_x,m_y);
        s_splat->drawOneShot(0);
        for(int i=0;i < int(segmentList.size());i++)
        {
            seg=&segmentList[i];

            s_splat->setXY(seg->getX(),seg->getY());
            s_splat->drawOneShot(0);     
        }
        if (s_splat->getCurrentFrame()==2 && m_playSound==0)
        {
            if (Mix_Playing(6)==0)
                Mix_PlayChannel(6,snd_splat,0);
            m_playSound=1;
        }
    }




}
void snake::setXY(int x,int y){m_x=x; m_y=y;}

void snake::addSegment()
{
    segment *seg;

    if(segmentList.size()==0)
    {
        seg= new segment(m_x,m_y,m_SIZE,m_SIZE);
        segmentList.push_back(*seg);
    }
    else
    {
        int m_x2=segmentList[segmentList.size()-1].getX();
        int m_y2=segmentList[segmentList.size()-1].getY();
        seg= new segment(m_x2,m_y2,m_SIZE,m_SIZE);
        segmentList.push_back(*seg);
    }
    delete seg;
}
void snake::removeSegment()
{
    if (segmentList.size()==0)
        m_dead=true;
    else
        segmentList.erase(segmentList.end());

}

void snake::move(int dir)
{
    if(!m_dead)
    {
        /*if (m_player==1)
        {
            snd_sel=rand()%3;
            if (snd_sel==0)
            {
                if (Mix_Playing(13)==0)
                    Mix_PlayChannel(13,snd_kriech1,0);
                if (Mix_Playing(14)==0)
                    Mix_PlayChannel(14,snd_kriech2,0);
                if (Mix_Playing(15)==0)
                    Mix_PlayChannel(15,snd_kriech3,0);
                if (Mix_Playing(16)==0)
                    Mix_PlayChannel(16,snd_kriech4,0);
            }
        }
        if (m_player==2)
        {
            snd_sel=rand()%3;
            if (snd_sel==0)
            {
                if (Mix_Playing(9)==0)
                    Mix_PlayChannel(9,snd_kriech1,0);
                if (Mix_Playing(10)==0)
                    Mix_PlayChannel(10,snd_kriech2,0);
                if (Mix_Playing(11)==0)
                    Mix_PlayChannel(11,snd_kriech3,0);
                if (Mix_Playing(12)==0)
                    Mix_PlayChannel(12,snd_kriech4,0);
            }
        }*/

        m_dir=dir;
        if (m_dir==0)
            m_x+=SPEED;
        if (m_dir==1)
            m_y+=SPEED;
        if (m_dir==2)
            m_x-=SPEED;
        if (m_dir==3)
            m_y-=SPEED;

        if (m_x > 1920+64)
            m_x=1920+64;
        if (m_x < -64)
            m_x=-64;

        if (m_y > 1080+64)
            m_y=1080+64;
        if (m_y < -64)
            m_y=-64;

        for( int i=0; i< int(segmentList.size()); i++)
        {
            if (i==0)
                segmentList[i].addPos(m_x,m_y);
            else
                segmentList[i].addPos(segmentList[i-1].getX(),segmentList[i-1].getY());

            segmentList[i].followTo(SPEED);
            if(i>=2)
                if (_collision.rect({segmentList[i].getX(),segmentList[i].getY(),64-15,64-15},{m_x,m_y,64,64})==1)
                {
                    m_dead=true;

                 }
        }

    }    

}
void snake::setDir(int d)
{
    m_dir=d;
}
void snake::setDead(bool dead){m_dead=dead;}

void snake::clear()
{
    segmentList.clear();
    posList.clear();
}

int snake::getX(){return m_x;}
int snake::getY(){return m_y;}
segment *snake::getSeg(int i){return &segmentList[i];}
int snake:: getSize(){return segmentList.size();}
int snake::getDir(){return m_dir;}
bool snake::getDead(){return m_dead;}

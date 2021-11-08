#ifndef SNAKE_H
#define SNAKE_H
#include<SDL2/SDL_mixer.h>
#include <vector>
#include "sprite.h"
#include "segment.h"
#include "collision.h"
using namespace std;

class snake
{
public:
    snake(SDL_Renderer *rnd,int player);
    ~snake();
    void draw(int animation);
    void setXY(int x,int y);
    void addSegment();
    void removeSegment();
    void move(int dir);
    void setDir(int d);
    void setDead(bool dead);
    void clear();
    int getX();
    int getY();
    segment* getSeg(int i);
    int getSize();
    int getDir();
    bool getDead();


private:
    SDL_Renderer *_rnd;
    int SPEED=6,m_SIZE=32, segCount=0;

    int m_x=0,m_y=0,m_oldX=0,m_oldY=0,m_size,m_jump,m_segments,m_dir=0,m_playSound=0;
    sprite *s_animation[4],*s_segment,*s_splat;
    vector<segment> segmentList;
    vector<vector2d>posList;
    bool m_dead=false;
    collision _collision;
    Mix_Chunk *snd_splat;
    Mix_Chunk *snd_kriech1;
    Mix_Chunk *snd_kriech2;
    Mix_Chunk *snd_kriech3;
    Mix_Chunk *snd_kriech4;
    Mix_Chunk *snd_kriech5;
    int snd_sel=0;
    int m_player=1;

};

#endif // SNAKE_H

#ifndef SPRITE_H
#define SPRITE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <iostream>
#include <string>
using namespace std;


class sprite
{
public:
    sprite(SDL_Renderer *rnd, string path);
    void setXY(int x, int y);
    void setScale(int scale);
    void setVisible(bool visible);
    void draw();
    void drawFrames(short flip);
    void drawFrame(int Frame,short flip);
    void drawOneShot(short flip);
    void resetOneShot();
    void loadGraphic(string path);
    void createFrame(int colum,int row); //Cut out the Pictures and Save in Vector
    void createAnimation(int from, int to); //Select the animation Pictures
    void resetCurrentFrame();
    void setAnimationSpeed(int i);
    void setAlpha(int alpha);
    int getCurrentFrame();
    int getMaxFrames();
private:

    SDL_Renderer *m_rnd;
    SDL_Texture *m_texture;
    Uint32 m_ticks,m_offset=0;
    SDL_Rect r_src,r_dest,r_frame;
    short m_from,m_to, m_flip=0;
    int m_scale=1,m_x=0,m_y=0,m_currentFrame=0, m_animationspeed=100,m_maxFrames=0;
    vector <SDL_Rect> v_frames;
    bool m_play=true,m_visible=true;
    short oneShotState=0;
};

#endif // SPRITE_H

#include "sprite.h"

sprite::sprite(SDL_Renderer *rnd, string path)
{
   m_rnd=rnd;

   loadGraphic(path);
}
void sprite::setXY(int x, int y)
{
    r_dest.x=x;
    r_dest.y=y;


}
void sprite::setScale(int scale)
{
    m_scale=scale;
}
void sprite::draw()
{
    SDL_Rect tmp=r_dest;
    tmp.x=r_dest.x-(m_scale/2);
    tmp.y=r_dest.y-(m_scale/2);
    tmp.w=r_dest.w+m_scale;
    tmp.h=r_dest.h+m_scale;
    if (m_visible)
    {
        if (m_flip==0)
            SDL_RenderCopyEx(m_rnd,m_texture,&r_src,&tmp,0,0,SDL_FLIP_NONE);
        if (m_flip==1)
            SDL_RenderCopyEx(m_rnd,m_texture,&r_src,&tmp,0,0,SDL_FLIP_HORIZONTAL);
        if (m_flip==2)
            SDL_RenderCopyEx(m_rnd,m_texture,&r_src,&tmp,0,0,SDL_FLIP_VERTICAL);
    }
}
void sprite::setVisible(bool visible)
{
    m_visible=visible;
}
void sprite::drawFrames(short flip)
{
    SDL_Rect tmp;
    if (m_play)
    {

        //m_currentFrame=1;
        tmp=v_frames[m_currentFrame];
        tmp.x=r_dest.x-(m_scale/2);
        tmp.y=r_dest.y-(m_scale/2);
        tmp.w=tmp.w+m_scale;
        tmp.h=tmp.h+m_scale;

        if(m_visible)
        {
            if (flip==0)
                SDL_RenderCopyEx(m_rnd,m_texture,&v_frames[m_currentFrame],&tmp,0,0,SDL_FLIP_NONE);
            if (flip==1)
                SDL_RenderCopyEx(m_rnd,m_texture,&v_frames[m_currentFrame],&tmp,0,0,SDL_FLIP_HORIZONTAL);
            if (flip==2)
                SDL_RenderCopyEx(m_rnd,m_texture,&v_frames[m_currentFrame],&tmp,0,0,SDL_FLIP_VERTICAL);
            m_ticks= SDL_GetTicks()-m_offset;
            m_currentFrame = (m_ticks / m_animationspeed) % m_to;

        }
    }
}
void sprite::drawFrame(int Frame,short flip){
    SDL_Rect tmp;
    tmp=v_frames[m_currentFrame];
    tmp.x=r_dest.x-(m_scale/2);
    tmp.y=r_dest.y-(m_scale/2);
    tmp.w=tmp.w+m_scale;
    tmp.h=tmp.h+m_scale;
    if(m_visible)
    {

        if (flip==0)
            SDL_RenderCopyEx(m_rnd,m_texture,&v_frames[Frame],&tmp,0,0,SDL_FLIP_NONE);
        if (flip==1)
            SDL_RenderCopyEx(m_rnd,m_texture,&v_frames[Frame],&tmp,0,0,SDL_FLIP_HORIZONTAL);
        if (flip==2)
            SDL_RenderCopyEx(m_rnd,m_texture,&v_frames[Frame],&tmp,0,0,SDL_FLIP_VERTICAL);

    }
}

void sprite::drawOneShot(short flip)
{
    SDL_Rect tmp;

    if (oneShotState==0)
    {
        m_offset=SDL_GetTicks();
        oneShotState=1;
    }

        tmp=v_frames[m_currentFrame];
        tmp.x=r_dest.x-(m_scale/2);
        tmp.y=r_dest.y-(m_scale/2);
        tmp.w=tmp.w+m_scale;
        tmp.h=tmp.h+m_scale;
        if (oneShotState<2){
            if (flip==0)
                SDL_RenderCopyEx(m_rnd,m_texture,&v_frames[m_currentFrame],&tmp,0,0,SDL_FLIP_NONE);
            if (flip==1)
                SDL_RenderCopyEx(m_rnd,m_texture,&v_frames[m_currentFrame],&tmp,0,0,SDL_FLIP_HORIZONTAL);
            if (flip==2)
                SDL_RenderCopyEx(m_rnd,m_texture,&v_frames[m_currentFrame],&tmp,0,0,SDL_FLIP_VERTICAL);
        }
        else
        {
            if (flip==0)
                SDL_RenderCopyEx(m_rnd,m_texture,&v_frames[v_frames.size()-1],&tmp,0,0,SDL_FLIP_NONE);
            if (flip==1)
                SDL_RenderCopyEx(m_rnd,m_texture,&v_frames[v_frames.size()-1],&tmp,0,0,SDL_FLIP_HORIZONTAL);
            if (flip==2)
                SDL_RenderCopyEx(m_rnd,m_texture,&v_frames[v_frames.size()-1],&tmp,0,0,SDL_FLIP_VERTICAL);
        }
            m_ticks= SDL_GetTicks()-m_offset;
            m_currentFrame = (m_ticks / m_animationspeed) % m_to;
            if (m_currentFrame==int(v_frames.size())-1)
                oneShotState=3;

}
void sprite::resetOneShot()
{
    oneShotState=0;
    m_currentFrame=0;
}


void sprite::loadGraphic(string path)
{
    SDL_Surface *tmp;
    tmp=IMG_Load(path.c_str());
    if (tmp==NULL) cout <<path <<" No file!"<< endl;
    m_texture= SDL_CreateTextureFromSurface(m_rnd,tmp);
    r_src.w= tmp->w;
    r_src.h= tmp->h;
    r_src.x= 0;
    r_src.y= 0;
    r_dest=r_src;
    SDL_SetTextureBlendMode( m_texture, SDL_BLENDMODE_BLEND);
    SDL_FreeSurface(tmp);
}

void sprite::createFrame(int colum,int row)
{
    SDL_Rect tmp;

    for (int iy=0; iy< r_src.h; iy+=int((r_src.h / row)))
    {
        for (int ix=0; ix< r_src.w; ix+=int((r_src.w / colum)))
        {
            tmp.x=ix;
            tmp.y=iy;
            tmp.w=(r_src.w / colum);
            tmp.h=(r_src.h / row);
            v_frames.push_back(tmp);

        }

    }
    m_to=v_frames.size();
}
   void sprite::createAnimation(int from, int to)
   {
        m_from=from;
        m_to=to;

   }

    void sprite::resetCurrentFrame()
    {
        m_offset=SDL_GetTicks();
    }
    void sprite::setAnimationSpeed(int i)
    {
        m_animationspeed=i;
    }
    void sprite::setAlpha(int alpha)
    {
        SDL_SetTextureAlphaMod( m_texture, alpha );
    }
   int sprite::getCurrentFrame()
   {
       return m_currentFrame;
   }
   int sprite::getMaxFrames(){return m_to;}

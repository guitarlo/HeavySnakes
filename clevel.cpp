#include "clevel.h"

clevel::clevel(int screenW,int screenH,int *tileSize, int *scale)
{
    m_screenW=screenW;
    m_screenH=screenH;
    p_tileSize=tileSize;
    p_scale=scale;
    s_tile tmp;


        for (int x=0; x< (m_screenW / *tileSize) ; x++)
        {
            tmp.x=x;
            tmp.y=0;
            tmp.size=*tileSize;
            tmp.n=2;
            mapLevel.push_back(tmp);

            tmp.x=x;
            tmp.y=1;
            tmp.size=*tileSize;
            tmp.n=1;
            mapLevel.push_back(tmp);

            tmp.x=x;
            tmp.y= (m_screenH / *tileSize)-1;
            tmp.size=*tileSize;
            tmp.n=2;
            mapLevel.push_back(tmp);

            tmp.x=x;
            tmp.y= (m_screenH / *tileSize);
            tmp.size=*tileSize;
            tmp.n=1;
            mapLevel.push_back(tmp);


        }

       //Spikes
        for (int x=((m_screenW / *tileSize)/2)-2; x < ((m_screenW / *tileSize)/2)+2 ; x++)
        {
            tmp.x=x;
            tmp.y=(m_screenH / *tileSize)/2;
            tmp.size=*tileSize;
            tmp.n=3;
            mapLevel.push_back(tmp);

        }

        for (int y=0; y < (m_screenH / *tileSize)-1 ; y++)
        {
            tmp.x=0;
            tmp.y=y;
            tmp.size=*tileSize;
            tmp.n=2;
            mapLevel.push_back(tmp);

            tmp.x= (m_screenW / *tileSize)-1;
            tmp.y=y;
            tmp.size=*tileSize;
            tmp.n=2;
            mapLevel.push_back(tmp);

        }

    //Lava Corners
    tmp.x=1;
    tmp.y=2;
    tmp.n=4;
    mapLevel.push_back(tmp);

    tmp.x=(m_screenW / *tileSize)-2;
    tmp.y=2;
    tmp.n=4;
    mapLevel.push_back(tmp);

    tmp.x=1;
    tmp.y=(m_screenH / *tileSize)-2;
    tmp.n=4;
    mapLevel.push_back(tmp);

    tmp.x=(m_screenW / *tileSize)-2;
    tmp.y=(m_screenH / *tileSize)-2;
    tmp.n=4;
    mapLevel.push_back(tmp);



}
int clevel::getX(int n){return mapLevel[n].x;}


int clevel::getY(int n){return mapLevel[n].y;}
bool clevel::getPassable(int n){return mapLevel[n].passable;}
bool clevel::getDangerous(int n){return mapLevel[n].dangerous;}

int clevel::getTile(int n)
{
    return mapLevel[n].n;
}

int clevel::getSize()
{
    return mapLevel.size();
}

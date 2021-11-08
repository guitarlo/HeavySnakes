#include "icelevel.h"

icelevel::icelevel(int screenW,int screenH,int *tileSize, int *scale)
{
    m_screenW=screenW;
    m_screenH=screenH;
    p_tileSize=tileSize;
    p_scale=scale;
    _tile tmp;


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

       //Lava
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

}
int icelevel::getX(int n){return mapLevel[n].x;}


int icelevel::getY(int n){return mapLevel[n].y;}
bool icelevel::getPassable(int n){return mapLevel[n].passable;}
bool icelevel::getDangerous(int n){return mapLevel[n].dangerous;}

int icelevel::getTile(int n)
{
    return mapLevel[n].n;
}

int icelevel::getSize()
{
    return mapLevel.size();
}




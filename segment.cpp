#include "segment.h"

segment::segment(int x, int y, int w, int h )
{
    m_x=x;
    m_y=y;
    m_w=w;
    m_h=h;

}
void segment::followTo(int speed)
{
    vector2d temp=posList[counter];
    if (m_wait >= 10){
        if (m_x < temp.x)
            m_x+=speed;
        if (m_x > temp.x)
            m_x-=speed;
        if (m_y > temp.y)
            m_y-=speed;
        if (m_y < temp.y)
            m_y+=speed;
    }else
        m_wait++;

    if (m_x==temp.x and
        m_y==temp.y)
        posList.erase(posList.begin());
}
void segment::addPos(int x, int y)
{
    vector2d pos;
    pos.x=x;
    pos.y=y;
    posList.push_back(pos);
}
void segment::setXY(int x, int y)
{
    m_x=x;
    m_y=y;
}

void segment::resetWait()
{
    m_wait=0;
}
int segment::getX()
{
    return m_x;
}
int segment::getY()
{
    return m_y;
}


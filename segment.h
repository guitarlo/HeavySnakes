#ifndef SEGMENT_H
#define SEGMENT_H
#include <vector>
#include<iostream>
#include <collision.h>
using namespace std;
struct vector2d
{
    int x,y;
};

class segment
{
public:
    segment(int x, int y, int w, int h );
    void followTo(int speed);
    void addPos(int x, int y);
    void setXY(int x, int y);
    void resetWait();
    int getX();
    int getY();

    vector2d getXY();
    int getCounter(){return counter;}
private:
    collision _collision;
    int m_x,m_y,m_w,m_h,m_SIZE,m_wait=0;
    vector<vector2d>posList;
    int counter=0;
};

#endif // SEGMENT_H

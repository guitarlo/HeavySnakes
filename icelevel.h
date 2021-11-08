#ifndef ICELEVEL_H
#define ICELEVEL_H
#include <vector>
using namespace std;
struct _tile
{
    int x, y, size,n;
    bool passable=false;
    bool dangerous=false;


};
class icelevel
{
public:
    icelevel(int screenW,int screenH,int *tileSize, int *scale);
    int getX(int n);
    int getY(int n);
    bool getPassable(int n);
    bool getDangerous(int n);
    int getTile(int n);
    int getSize();
private:
    int m_screenW,m_screenH, *p_tileSize,*p_scale;
    vector<_tile> mapLevel;

};

#endif // ICELEVEL_H

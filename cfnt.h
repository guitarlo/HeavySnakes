#ifndef CFNT_H
#define CFNT_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <sstream>
#include <iostream>
#include <string>
using namespace std;
class cfnt
{
    public:
        cfnt(SDL_Renderer* rnd,string name, int fsize);
        virtual ~cfnt();
        void fntWrite(string txt, int x, int y, bool transparence);
		void setSize(int s);
		void setFrontColor(int r, int g, int b);
		void setBgColor(int r, int g, int b,int a);
		void setAlpha(int a);
        string intToStr(int i);
    protected:

    private:
    TTF_Font *font;
    SDL_Color fc{ 255,255,255,0 }, bc{ 0,0,0,0 };
    SDL_Renderer *_rnd;


	int fsize;


};
#endif // CFNT_H

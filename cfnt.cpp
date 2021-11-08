#include "cfnt.h"

cfnt::cfnt(SDL_Renderer *rnd,string fnt, int fsize)
{


    font = TTF_OpenFont( fnt.c_str(), fsize );
    if (font==NULL)
    {
        cout << " Failed to load font : " << SDL_GetError() << endl;

    }
    _rnd=rnd;


}

cfnt::~cfnt()
{

}
void cfnt::fntWrite(string txt, int x, int y,bool transparence)
{
	SDL_Surface *s;
	SDL_Texture *t;
	if (transparence)
        s = TTF_RenderText_Shaded(this->font, txt.c_str(), this->fc, SDL_Color{255, 0, 255,0});
	else
		s = TTF_RenderText_Shaded(this->font, txt.c_str(), this->fc, bc);

	SDL_SetColorKey(s, SDL_TRUE, SDL_MapRGB(s->format, 255, 0, 255));


    t = SDL_CreateTextureFromSurface(_rnd, s);
        int w = s->w;
        int h = s->h;
        SDL_Rect r{ x,y,w,h };

        SDL_RenderCopy(_rnd, t,NULL, &r);
        SDL_FreeSurface(s);
        SDL_DestroyTexture(t);
}
void cfnt::setSize(int s)
{
	this->fsize = s;
}
void cfnt::setFrontColor(int r, int g, int b)
{
	this->fc.r = r;
	this->fc.g = g;
	this->fc.b= b;


}
void cfnt::setBgColor(int r, int g, int b, int a)
{
	this->bc.r = r;
	this->bc.g = g;
	this->bc.b = b;
	this->bc.a = a;
}

void cfnt::setAlpha(int a)
{
	if(a<=255)
	this->fc.a = a;
}
string cfnt::intToStr(int i)
{
   string s;
   stringstream ss;
   ss <<i;
   ss>>s;
   return s;

}

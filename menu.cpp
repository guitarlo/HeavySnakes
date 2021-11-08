#include "menu.h"

Menu::Menu(SDL_Renderer *rnd,int *screenW, int *screenH)
{
    _rnd=rnd;
    _run=true;
    js=SDL_JoystickOpen(0);
    _screenW=screenW;
    _screenH=screenH;

}

int Menu::showMenu()
{
    sprite titel(_rnd,"GFX/Titel.png");
    sprite wall(_rnd,"GFX/wall.png");
    sprite box(_rnd,"GFX/Box.png");
    box.createFrame(4,1);
    box.setScale(100);
    box.setXY(300,300);
    sprite button(_rnd,"GFX/Button.png");

    cfnt font(_rnd,"FNT/jabjai_heavy.TTF",48);
    cfnt font2(_rnd,"FNT/jabjai_heavy.TTF",20);
    font.setFrontColor(255,255,255);
    font.setBgColor(255,0,0,255);

    Mix_Music* music=Mix_LoadMUS("MUSIC/Snake.mp3");
    Mix_Chunk *snd_hmm= Mix_LoadWAV("SND/hmm.wav");
    Mix_Chunk *snd_eat1= Mix_LoadWAV("SND/eat1.wav");
    Mix_VolumeMusic(50);
    Mix_PlayMusic(music,-1);
    int choose=1,bY=0;
    int menu=0;
    int player=0;
    while(_run)
    {
        SDL_RenderClear(_rnd);

        for (int x=0; x< *_screenW;x+=64)
        {
            for (int y=0; y< *_screenH;y+=64)
            {
                wall.setXY(x,y);
                wall.draw();

            }

        }


        while(SDL_PollEvent(&e))
        {

            if(e.type==SDL_QUIT)
                _run=false;
            if(e.type==SDL_KEYDOWN)
            {
                if(e.key.keysym.sym==SDLK_UP)
                {
                    choose-=1;
                    Mix_PlayChannel(-1,snd_eat1,0);
                }
                if(e.key.keysym.sym==SDLK_DOWN)
                 {
                    choose+=1;
                    Mix_PlayChannel(-1,snd_eat1,0);
                }
                if(e.key.keysym.sym==SDLK_RETURN)
                {
                    Mix_PlayChannel(1,snd_hmm,0);
                    while(Mix_Playing(1))
                    {

                    }
                    if (choose==3){
                        if (menu==0)
                            _run=false;

                        if (menu==1)
                            menu=0;

                    }


                    if (choose==1){
                        if (menu==1)
                        {
                            game g(_rnd,player,_screenW,_screenH);
                            g.run();
                            menu=0;
                        }
                        if (menu==0)
                        {
                            player=1;
                            menu=1;
                        }

                    }
                     if (choose==2){

                         if (menu==1)
                         {
                             snowGame g(_rnd,player,_screenW,_screenH);
                             g.run();
                             menu=0;
                         }
                         if (menu==0)
                         {
                            player=2;
                            menu=1;
                         }
                    }
                }
            }
            if (SDL_JoystickGetHat(js,0)==SDL_HAT_UP)
            {
                choose-=1;
                Mix_PlayChannel(-1,snd_eat1,0);
            }
            if (SDL_JoystickGetHat(js,0)==SDL_HAT_DOWN)
            {
                choose+=1;
                Mix_PlayChannel(-1,snd_eat1,0);
            }
            if(SDL_JoystickGetButton(js,SDL_CONTROLLER_BUTTON_A)!=0)
            {
                Mix_PlayChannel(1,snd_hmm,0);
                while(Mix_Playing(1))
                {

                }

                if (choose==3){
                    if (menu==0)
                        _run=false;

                    if (menu==1)
                        menu=0;

                }


                if (choose==1){
                    if (menu==1)
                    {
                        game g(_rnd,player,_screenW,_screenH);
                        g.run();
                        menu=0;
                    }
                    if (menu==0)
                    {
                        player=1;
                        menu=1;
                    }

                }
                 if (choose==2){

                     if (menu==1)
                     {
                         snowGame g(_rnd,player,_screenW,_screenH);
                         g.run();
                         menu=0;
                     }
                     if (menu==0)
                     {
                        player=2;
                        menu=1;
                     }
                }
            }

        }
        titel.setXY(*_screenW/2-(900/2),0);
        titel.draw();

        button.setXY(*_screenW/2-(400/2),260);
        button.draw();

        button.setXY(*_screenW/2-(400/2),380);
        button.draw();

        button.setXY(*_screenW/2-(400/2),500);
        button.draw();

        if (choose==1)
            bY=300;
        if (choose==2)
            bY=420;
        if (choose==3)
            bY=540;
        if (choose>3)
            choose=1;
        if(choose<1)
            choose=3;

        box.setXY((*_screenW/2)-320,bY);
        box.drawFrames(0);
        box.setXY((*_screenW/2)+250,bY);
        box.drawFrames(1);

        if (menu==0)
        {
            font.fntWrite("New Game",(*_screenW/2)-110,290,true);
            font.fntWrite("2 Player",(*_screenW/2)-110,410,true);
            font.fntWrite("Quit",(*_screenW/2)-100,540,true);
            font2.fntWrite("A game by Carlo Mansfed - Scorebox-Studio.de ",10,*_screenH-20,true);
        }
        if (menu==1)
        {
            font.fntWrite("Castle",(*_screenW/2)-110,290,true);
            font.fntWrite("IceWorld",(*_screenW/2)-110,410,true);
            font.fntWrite("Back",(*_screenW/2)-100,540,true);
            font2.fntWrite("A game by Carlo Mansfed - Scorebox-Studio.de ",10,*_screenH-20,true);
        }

        SDL_RenderPresent(_rnd);



    }
    SDL_JoystickClose(js);
    Mix_HaltMusic();
    Mix_FreeMusic(music);
    Mix_FreeChunk(snd_hmm);
    Mix_FreeChunk(snd_eat1);


return 0;
}

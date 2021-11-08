#include "snowgame.h"

snowGame::snowGame(SDL_Renderer *rnd,int player, int *screenW , int *screenH)
{
    _rnd=rnd;
    cout <<"Start Game..."<<endl;
    _run=true;
    m_Player=player;
    m_screenW= *screenW;
    m_screenH= *screenH;




        js1=SDL_JoystickOpen(0);
        jsh1=SDL_HapticOpenFromJoystick(js1);
        if( jsh1 == NULL )
        {
           cout <<"No Haptic!"<< endl;
        }
        else
        {
            if( SDL_HapticRumbleInit(jsh1) < 0 )
            {
                cout <<"No Haptic!"<< endl;
            }
        }
        js2=SDL_JoystickOpen(1);
        jsh2=SDL_HapticOpenFromJoystick(js2);
        if( jsh2 == NULL )
        {
            cout <<"No Haptic!"<< endl;
        }
        else
        {
            if( SDL_HapticRumbleInit(jsh2) < 0 )
            {
                cout <<"No Haptic!"<< endl;
            }
        }
}


void snowGame::run()
{
    Uint32 startTimer,delayTimer;

    icelevel _level(m_screenW,m_screenH,&_tileSize,&m_scale);
    collision _collision;

    Mix_Chunk *snd_body=Mix_LoadWAV("SND/body.wav");

    Mix_Chunk *snd_eat1= Mix_LoadWAV("SND/Eat_crush.wav");
    Mix_Chunk *snd_eat2= Mix_LoadWAV("SND/Eat_crush2.wav");
    Mix_Chunk *snd_eat3= Mix_LoadWAV("SND/eat3.wav");
    Mix_Chunk *snd_robby_kill= Mix_LoadWAV("SND/Robby_dead.wav");
    Mix_Chunk *snd_robbo_air= Mix_LoadWAV("SND/fresh_air.wav");

    Mix_VolumeChunk(snd_eat1,50);
    Mix_VolumeChunk(snd_eat2,50);
    Mix_VolumeChunk(snd_eat3,50);

    Mix_Chunk *snd_splat= Mix_LoadWAV("SND/Splat.wav");
    Mix_VolumeChunk(snd_splat,100);


    sprite robbo(_rnd,"GFX/Robbo.png");
    sprite tiles(_rnd,"GFX/Snow_Set.png");
    tiles.createFrame(5,1);

    sprite lava(_rnd,"GFX/Lava.png");
    lava.createFrame(9,1);

    snake _snake(_rnd,1);
    _snake.setXY((3*64),(3*64));
    _snake.addSegment();
    sprite egg1(_rnd,"GFX/Egg.png");
        egg1.createFrame(14,1);
        egg1.setScale(40);
        egg1.setXY(3*_tileSize,3*_tileSize);


    snake _snake2(_rnd,2);
    _snake2.setXY(m_screenW-(3*_tileSize),(3*_tileSize));
    _snake2.addSegment();
    sprite egg2(_rnd,"GFX/Egg.png");
        egg2.createFrame(14,1);
        egg2.setScale(40);
        egg2.setXY(m_screenW-(3*_tileSize),(3*_tileSize));

    crobby _orb(_rnd,&m_screenW,&m_screenH,&_tileSize);
    _orb.spawn();

    cfnt fnt_big(_rnd,"FNT/jabjai_heavy.TTF",64);
    ctimer t_startbad_guys,t_wait_to_spawn;
    int m_wait_to_spawn=0, m_bad_or_good_robby=0;

    m_dir=0;
    m_dir2=2;
    startState=0;
    srand(time(0));
    _orb.spawn();
    while(_run)
    {
        startTimer=SDL_GetTicks();


        if (_collision.rect({_snake.getX(),_snake.getY(),_tileSize,_tileSize},{_orb.getX(),_orb.getY(),_tileSize,_tileSize})==1)
        {
            if(m_bad_or_good_robby==3)
                _snake.setDead(true);
            Mix_PlayChannel(-1,snd_eat1,0);
            Mix_PlayChannel(-1,snd_robby_kill,0);

            _snake.addSegment();
            _orb.spawn();
            m_wait_to_spawn=rand()%4;
            m_wait_to_spawn+=3;

            t_wait_to_spawn.reset();
            m_bad_or_good_robby=rand()%4;


        }
        if (_collision.rect({_snake2.getX(),_snake2.getY(),_tileSize,_tileSize},{_orb.getX(),_orb.getY(),_tileSize,_tileSize})==1)
        {
            Mix_PlayChannel(-1,snd_eat1,0);
            Mix_PlayChannel(-1,snd_robby_kill,0);

            if(m_bad_or_good_robby==3)
                _snake2.setDead(true);

            _snake2.addSegment();
            _orb.spawn();
            m_wait_to_spawn=rand()%4;
            m_wait_to_spawn+=3;
            t_wait_to_spawn.reset();
            m_bad_or_good_robby=rand()%4;
        }
        if(int(t_wait_to_spawn.getTime()/1000)>= m_wait_to_spawn)
        {
            _orb.spawn();
            m_wait_to_spawn=rand()%4;
            m_wait_to_spawn+=3;;
            t_wait_to_spawn.reset();
            m_bad_or_good_robby=rand()%4;
        }





        // Ground
        for (int x=0; x<(m_screenW); x+=_tileSize+m_scale)
            for (int y=0; y<(m_screenH); y+=_tileSize+m_scale)
            {
                tiles.setScale(m_scale);
                tiles.setXY(x,y);
                tiles.drawFrame(0,0);
            }

        //Tiles Level
        for (int i=0; i< _level.getSize();i++)
        {
            tiles.setXY(_level.getX(i)*(_tileSize+m_scale),_level.getY(i)*(_tileSize+m_scale));
            tiles.setScale(m_scale);

            tiles.drawFrame(_level.getTile(i),0);
            if (_level.getTile(i)==4)
            {
                lava.setXY(_level.getX(i)*_tileSize,_level.getY(i)*_tileSize);
                lava.setScale(m_scale);
                lava.drawFrames(0);
            }
            // Collision Player 1
            if(_collision.rect({_snake.getX(),_snake.getY(),_tileSize,_tileSize},{_level.getX(i)*_tileSize,_level.getY(i)*_tileSize,_tileSize,_tileSize})==1)
                _snake.setDead(true);

            // Collision Player 2
            if (m_Player==2)
            {
                if(_collision.rect({_snake2.getX(),_snake2.getY(),_tileSize,_tileSize},{_level.getX(i)*_tileSize,_level.getY(i)*_tileSize,_tileSize,_tileSize})==1)
                    _snake2.setDead(true);
            }

            // Test free space for Orb
            if (_collision.rect({_orb.getX(),_orb.getY(),_tileSize,_tileSize},{_level.getX(i)*_tileSize,_level.getY(i)*_tileSize,_tileSize,_tileSize})==1)
            {
                _orb.spawn();
                i=0;
            }
        }




        while(SDL_PollEvent(&e))
        {
            if(e.type==SDL_QUIT)
                _run=false;
            if (e.type==SDL_KEYDOWN)
            {

                if (e.key.keysym.sym==SDLK_RIGHT)
                    m_dir=0;
                if (e.key.keysym.sym==SDLK_DOWN)
                    m_dir=1;
                if (e.key.keysym.sym==SDLK_LEFT)
                    m_dir=2;
                if (e.key.keysym.sym==SDLK_UP)
                    m_dir=3;
                if (e.key.keysym.sym==SDLK_SPACE)
                {
                        cbombs *tempBomb=new cbombs(_rnd,_snake.getSeg(_snake.getSize()-1)->getX(),_snake.getSeg(_snake.getSize()-1)->getY(),&_tileSize);
                        bomblist.push_back(*tempBomb);
                        _snake.removeSegment();
                         delete tempBomb;
                }
                if(m_Player==2)
                {
                    if (e.key.keysym.sym==SDLK_d)
                        m_dir2=0;
                    if (e.key.keysym.sym==SDLK_s)
                        m_dir2=1;
                    if (e.key.keysym.sym==SDLK_a)
                        m_dir2=2;
                    if (e.key.keysym.sym==SDLK_w)
                        m_dir2=3;
                    if (e.key.keysym.sym==SDLK_TAB)
                    {
                            cbombs *tempBomb=new cbombs(_rnd,_snake2.getSeg(_snake2.getSize()-1)->getX(),_snake2.getSeg(_snake2.getSize()-1)->getY(),&_tileSize);
                            bomblist.push_back(*tempBomb);
                            _snake2.removeSegment();
                            delete tempBomb;

                    }
                }
                if (e.key.keysym.sym==SDLK_ESCAPE)
                    _run=false;
                if (e.key.keysym.sym==SDLK_RETURN)
                {
                    _snake.clear();
                    _snake2.clear();
                    run();
                }
            }

            if(SDL_JoystickGetButton(js1,SDL_CONTROLLER_BUTTON_Y)!=0 or SDL_JoystickGetButton(js2,SDL_CONTROLLER_BUTTON_Y)!=0)
            {
                _snake.clear();
                _snake2.clear();
                run();
            }

            if(SDL_JoystickGetHat(js1,0)==SDL_HAT_UP)
                m_dir=3;
            if(SDL_JoystickGetHat(js1,0)==SDL_HAT_LEFT)
                m_dir=2;
            if(SDL_JoystickGetHat(js1,0)==SDL_HAT_DOWN)
                m_dir=1;
            if(SDL_JoystickGetHat(js1,0)==SDL_HAT_RIGHT)
                m_dir=0;
            if(SDL_JoystickGetHat(js2,0)==SDL_HAT_UP)
                m_dir2=3;
            if(SDL_JoystickGetHat(js2,0)==SDL_HAT_LEFT)
                m_dir2=2;
            if(SDL_JoystickGetHat(js2,0)==SDL_HAT_DOWN)
                m_dir2=1;
            if(SDL_JoystickGetHat(js2,0)==SDL_HAT_RIGHT)
                m_dir2=0;
            if(SDL_JoystickGetButton(js1,SDL_CONTROLLER_BUTTON_A))
            {
                cbombs *tempBomb=new cbombs(_rnd,_snake.getSeg(_snake.getSize()-1)->getX(),_snake.getSeg(_snake.getSize()-1)->getY(),&_tileSize);
                bomblist.push_back(*tempBomb);
                _snake.removeSegment();
                delete tempBomb;
            }
            if(SDL_JoystickGetButton(js2,SDL_CONTROLLER_BUTTON_A))
            {
                cbombs *tempBomb=new cbombs(_rnd,_snake2.getSeg(_snake2.getSize()-1)->getX(),_snake2.getSeg(_snake2.getSize()-1)->getY(),&_tileSize);
                bomblist.push_back(*tempBomb);
                _snake2.removeSegment();
                delete tempBomb;
            }

            if(SDL_JoystickGetButton(js1,SDL_CONTROLLER_BUTTON_START)!=0 or SDL_JoystickGetButton(js2,SDL_CONTROLLER_BUTTON_START)!=0)
            {
                _run=false;
            }


        }

        if (m_Player==2)
        {
            if (!_snake2.getDead() && !_snake.getDead())
            {
                if (_collision.rect({_snake.getX(),_snake.getY(),_tileSize,_tileSize},{_snake2.getX(),_snake2.getY(),_tileSize,_tileSize})==1)
                {                
                    _snake.setDead(true);
                    _snake2.setDead(true);
                }
            }


            if(!_snake2.getDead())
            {
                for(int i=0; i< _snake2.getSize(); i++)
                    if (_collision.rect({_snake.getX(),_snake.getY(),64+m_scale,64+m_scale},{_snake2.getSeg(i)->getX(),_snake2.getSeg(i)->getY(),64+m_scale,64+m_scale})==1)
                    {
                        if(i==_snake2.getSize()-1)
                        {
                            if (!_snake.getDead())
                            {
                                Mix_PlayChannel(-1,snd_eat2,0);
                                _snake2.removeSegment();
                                _snake.addSegment();
                            }
                        }
                        else
                            _snake.setDead(true);

                        cout << "Dead by Snake2"<< endl;

                         SDL_HapticRumblePlay(jsh1, 0.75, 500 );
                    }

            }



            if(!_snake.getDead())
            {
                for(int i=0; i< _snake.getSize(); i++)
                    if (_collision.rect({_snake2.getX(),_snake2.getY(),64+m_scale,64+m_scale},{_snake.getSeg(i)->getX(),_snake.getSeg(i)->getY(),64+m_scale,64+m_scale})==1)
                    {
                        if(i==_snake.getSize()-1)
                        {
                            if (!_snake2.getDead())
                            {
                                Mix_PlayChannel(-1,snd_eat2,0);
                                _snake.removeSegment();
                                _snake2.addSegment();
                            }
                        }
                        else
                            _snake2.setDead(true);
                        cout << "Dead by Snake1"<< endl;



                         SDL_HapticRumblePlay(jsh2, 0.75, 500 );
                    }
             }
        }


        if(t_startbad_guys.getTime()/1000>=3)
            _orb.draw(m_bad_or_good_robby);
        else
            _orb.draw(0);


        _snake.draw(_snake.getDir());
        if(m_Player==2)
            _snake2.draw(_snake2.getDir());

        if (startState >=3)
        {
            _snake.move(m_dir);
            if (m_Player==2)
                _snake2.move(m_dir2);
        }
// Intro
        if (startState==0)
        {
            egg1.resetOneShot();
            egg2.resetOneShot();

            startState=1;
        }
        if (startState==1)
        {
            egg1.drawFrame(0,0);
            if(m_Player==2)
                egg2.drawFrame(0,0);
            if(message==1 || message==4)
                if (Mix_Playing(4)==0)                {
                    startState=2;
                    message=3;
                    egg1.resetOneShot();
                    egg2.resetOneShot();

                }

            if (message==0)
            {
                Mix_PlayChannel(4,snd_robbo_air,0);
                message=1;
            }

            robbo.setXY(50,m_screenH-140);
            robbo.setScale(150);
            robbo.draw();
        }

        if(startState==2)
        {
            if(message==4)
                if (Mix_Playing(6)==0)
                    startState=3;
            if(message==3)
            {
                Mix_PlayChannel(5,snd_splat,0);
                Mix_PlayChannel(6,snd_body,0);
                message=4;
            }
            egg1.drawOneShot(0);
            if(m_Player==2)
                egg2.drawOneShot(0);

        }

        if (m_Player==1)
        {
            if(_snake.getDead())
            {
                fnt_big.fntWrite("Points:", m_screenW/2-(10*64/2),m_screenH/2,true);
                fnt_big.fntWrite(fnt_big.intToStr(_snake.getSize()), m_screenW/2-(10*64/2),m_screenH/2+64,true);
            }
        }

        if(m_Player==2)
        {
            if (_snake.getDead() || _snake2.getDead())
            {
                if (_snake.getSize()> _snake2.getSize())
                    fnt_big.fntWrite("Player 1 Wins!", m_screenW/2-(10*64/2),m_screenH/2,true);
                else if(_snake.getSize() < _snake2.getSize())
                    fnt_big.fntWrite("Player 2 Wins!", m_screenW/2-(10*64/2),m_screenH/2,true);
                else
                    fnt_big.fntWrite("Player 1 = Player 2", m_screenW/2-(10*64/2),m_screenH/2,true);
            }

        }
        if (bomblist.size()>0)
        {
            for(int i=0; i < int(bomblist.size()); i++)
            {
                bomblist[i].update(&_snake);
                bomblist[i].update(&_snake2);

                if (bomblist[i].getDead())
                    bomblist.erase(bomblist.begin()+i);
            }
        }
        SDL_RenderPresent(_rnd);

        delayTimer=SDL_GetTicks()-startTimer;
       if(delayTimer < 1000/60)
       SDL_Delay((1000/60)-delayTimer);

    }
}

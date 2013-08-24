///         Projeej (Projengine)
///
///         Criado por Matheus Braga Almeida (Mock the bear)
///         Com auxilio de Gabriel Botelho
///         E professor Rodrigo Bonifácio
///
///         Materia Programação orientada a objetos 1/2013
///
///         Não redistribuir sem autorização de Matheus Braga
///

/*
    Informações para contato:
        Matheus Braga:
            matheus.mtb7@gmail.com

*/
#include <iostream>
#include <sstream>
#include <stdint.h> // uint8_t
#include <SDL/SDL.h>  //SDL, lib grafica usada
#include <SDL/SDL_image.h> //Usado para carregar facilmente imagens
#ifdef MULTITASK
#include <SDL/SDL_thread.h> //Usado para multi threading
#endif
#include <SDL/SDL_ttf.h>  // Usado para imprimir texto


#include <time.h> // Apenas para time() usado em srand();
#include <math.h>
#include "definitions.h"
#include "logs.h"
#include "luascript.h"
#include "imageloader.h"
#include "objects.h"
#include "effects.h"
#include "maploader.h"
#include "timer.h"
#include "keyboard.h"

#include "console.h"
#include "sound.h"
#include "polygon.h"
#include "particles.h"

#define NUMCHANNELS 24

using namespace std;

Timer fps; //Usado somente para regular FPS
Timer update,lua,inputs; //Calcular FPS real;
#ifdef MULTITASK
Timer timer_tr1; //Calcular FPS real; (usado em multitask)
Timer timer_tr2; //Calcular FPS real; (usado em multitask2)
SDL_Thread *thread1;
SDL_Thread *thread2;
#endif
SDL_Surface* display;                       //a tela.
extern bool registeredType[255];
extern User *user;                          // Classe do usuario para input
extern Map *game_map;                       //Mapa do jogo
                       //Obejto player, é controlado por teclado.
extern Console *consolemain;                // Console
extern Particle *mother_part;
extern Particle *last_part;
bool deleted = false;
int SCREEN_Width,SCREEN_Height,IMAGES_MAX;
luaScript *Lua;
Log *output;
using std::cerr;                            // Blegh
using std::endl;

void finish_him(){
    if (game_map)
        delete game_map;


    SDL_FreeSurface(display);
    Effect *swt = mother_ef,*prev;
    while(swt != NULL){
        prev = swt;
        swt = (Effect*)swt->next;
        delete prev;
    }
    Objeto *trocador = mother->next->next->next, *prv1;
    while(trocador != NULL){ //Usando lista
        prv1 = trocador;
        trocador = trocador->next;
        delete prv1;
    }
    for (int i=0;i<IMAGES_MAX;i++){
        SDL_FreeSurface(surfaceList[i]);
    }
    delete output;
    delete Lua;
    SDL_Quit();
    exit(0);
}


int animate(Effect *swt){

        while(swt != NULL){
            if(swt->alive && swt->canchangeFrame()){
                swt->skipFrane();
                if (swt->frameskip == 1){
                    if (swt->getFrame() == swt->getMaxFrames()-1 && swt->isLooping() == false){
                        swt->setAlive(false);
                    }
                }else{
                    if (swt->getFrame() <= 0 && swt->isLooping() == false){
                        swt->setAlive(false);
                    }
                }
            }
            swt = (Effect*)swt->next;
        }
        return 0;
}
Timer timer_tr1;

int game_control(Objeto *obj){
    char arh[] = "0";
        int tick = timer_tr1.get_ticks();
        while(obj != NULL){
            //Usando lista
            //Ação!
            bool proceed = true;
            if (!obj->alive)
                continue;
            /*LUA*/
            if (registeredType[obj->getType()]){
                lua_getglobal(Lua->L, "Game");
                lua_getfield(Lua->L, -1, "Object");
                arh[0] = obj->getType()+'0';
                lua_getfield(Lua->L, -1, arh);
                if(lua_isnil(Lua->L,-1)){
                  lua_pop(Lua->L, -1);
                }else if(lua_isfunction(Lua->L,-1)){
                    lua_pushinteger(Lua->L, obj->getType());
                    lua_pushinteger(Lua->L, obj->id);
                    if (lua_pcall(Lua->L, 2, 1, 0) != 0){
                        char *s = (char*)lua_tostring(Lua->L, -1);
                        if (consolemain)
                            consolemain->print(s);
                        output->write(s);
                        proceed = false;
                        lua_pop(Lua->L, -1);
                    }else{
                        proceed = lua_tointeger(Lua->L, -1) == 1;
                        lua_pop(Lua->L, -1);
                    }
                    lua_pop(Lua->L, -1);
                }
                lua_pop(Lua->L, -1);
            }
            if (proceed){
                if (obj->getType() == MOTION_OBJ){
                    if (obj->vX != 0 || obj->vY || 0){
                        float x = obj->getX()+obj->vX*(timer_tr1.get_ticks()/10.0);
                        float y = obj->getY()+obj->vY*(timer_tr1.get_ticks()/10.0);
                        float tx =x;
                        float ty =y;
                        if (game_map){
                            int col = 0;
                            int dir;
                            if (!obj->useclip)
                                col = game_map->getMap()->adjustXy(&x,&y,obj->getX(),obj->getY(),obj->getImage()->h,obj->getImage()->w,game_map->getX(),game_map->getY(),&dir,obj->id);
                            else
                                col = game_map->getMap()->adjustXy(&x,&y,obj->getX(),obj->getY(),obj->clips.h,obj->clips.w,game_map->getX(),game_map->getY(),&dir,obj->id);
                            bool continue_ = false;
                            if (col != 0 and (obj->id != col)){
                                //if (obj->state[0] != dir || obj->state[1] != col){

                                    lua_getglobal(Lua->L, "Game");
                                    lua_getfield(Lua->L, -1, "Collision");
                                    if(lua_isnil(Lua->L,-1)){
                                        lua_pop(Lua->L, -1);
                                    }else if(lua_isfunction(Lua->L,-1)){
                                        lua_pushinteger(Lua->L, obj->id);
                                        lua_pushinteger(Lua->L, col);
                                        lua_pushinteger(Lua->L, dir);
                                        if (lua_pcall(Lua->L, 3, 1, 0) != 0){
                                            char *s = (char*)lua_tostring(Lua->L, -1);
                                            if (consolemain)
                                                consolemain->print(s);
                                            output->write(s);
                                            lua_pop(Lua->L, -1);
                                            lua_pop(Lua->L, -1);

                                        }else{
                                            continue_ = lua_tointeger(Lua->L, -1) == 1;
                                            lua_pop(Lua->L, -1);
                                        }
                                }
                                lua_pop(Lua->L, -1);
                            }
                            if (game_map){
                                if (continue_)
                                    game_map->getMap()->moveObjById(obj,x,y,continue_);
                                else
                                    game_map->getMap()->moveObjById(obj,tx,ty,continue_);
                            }else{
                                obj->setXY(x,y);
                            }


                        }else{
                           if (game_map){
                                game_map->getMap()->moveObjById(obj,x,y,true);
                            }else{
                                obj->setXY(x,y);
                            }
                        }
                    }
                 }else if(obj->getType() == MOTION_OBJ_NO_BOUNDARY){
                    if (obj->vX != 0 || obj->vY || 0){
                        float x = obj->getX()+obj->vX*(timer_tr1.get_ticks()/10.0);
                        float y = obj->getY()+obj->vY*(timer_tr1.get_ticks()/10.0);
                        obj->setXY(x,y);
                    }
                 }else if(obj->getType() == MOTION_OBJ_BOUNCE_BOUNDARY){
                    if (obj->vX != 0 || obj->vY || 0){
                        float x = obj->getX()+obj->vX*(timer_tr1.get_ticks()/10.0);
                        float y = obj->getY()+obj->vY*(timer_tr1.get_ticks()/10.0);
                        if (x <= 0.0f)
                            obj->vX *= -1;
                        if (x >= (display->w - obj->getImage()->w))
                            obj->vX *= -1;
                        if (y <= 0.0f)
                            obj->vY *= -1;
                        if (y >= (display->h - obj->getImage()->h))
                            obj->vY *= -1;
                        obj->setXY(x,y);
                    }
                 }else if(obj->getType() == MOTION_MOUSE){
                    obj->setXY(user->MOUSE_X,user->MOUSE_Y);
                 }else if (obj->getType() == OBJ_MAP){
                    if (obj->vX != 0 || obj->vY || 0){
                        float x = obj->getX()+obj->vX*(timer_tr1.get_ticks()/10.0);
                        float y = obj->getY()+obj->vY*(timer_tr1.get_ticks()/10.0);
                        obj->setXY(x,y);
                        if (game_map)
                            for (int i=0;i<game_map->getObjCount();i++){
                                Objeto *currobj = game_map->map_objs[i];
                                currobj->ofx = x;
                                currobj->ofy = y;
                            }
                    }
                 }else if (obj->getType() == OBJ_GRAVITY){
                    if (obj->vX != 0 || obj->tY != 0){ //

                        float x = obj->getX()+obj->vX*(tick/(10.0));
                        float y = obj->getY()+obj->tY*(tick/(10.0)); // tY = velocidade em Y que vai variar até atingit vY
                        if (obj->tY > obj->vY){
                             obj->tY = obj->tY-obj->gY*(tick/(10.0));
                        }else if(obj->tY < obj->vY){
                            obj->tY = obj->tY+obj->gY*(tick/(10.0));
                        }
                        int dir;
                        if (game_map){
                            bool canrun=true;
                            int col = 0;
                            if (!obj->useclip)
                                col = game_map->getMap()->adjustXy(&x,&y,obj->getX(),obj->getY(),obj->getImage()->h,obj->getImage()->w,game_map->getX(),game_map->getY(),&dir,obj->id);
                            else
                                col = game_map->getMap()->adjustXy(&x,&y,obj->getX(),obj->getY(),obj->clips.h,obj->clips.w,game_map->getX(),game_map->getY(),&dir,obj->id);

                            if (col != 0){
                                if (obj->state[0] != dir || obj->state[1] != col){
                                    lua_getglobal(Lua->L, "Game");
                                    lua_getfield(Lua->L, -1, "Collision");
                                    if(lua_isnil(Lua->L,-1)){
                                        lua_pop(Lua->L, -1);
                                    }else if(lua_isfunction(Lua->L,-1)){
                                        lua_pushinteger(Lua->L, obj->id);
                                        lua_pushinteger(Lua->L, col);
                                        lua_pushinteger(Lua->L, dir);
                                        if (lua_pcall(Lua->L, 3, 1, 0) != 0){
                                            char *s = (char*)lua_tostring(Lua->L, -1);
                                            if (consolemain)
                                                consolemain->print(s);
                                            output->write(s);
                                            canrun = false;
                                            lua_pop(Lua->L, -1);
                                            lua_pop(Lua->L, -1);

                                        }else{
                                            canrun = lua_tointeger(Lua->L, -1) == 1;
                                            lua_pop(Lua->L, -1);
                                        }
                                        lua_pop(Lua->L, -1);
                                        obj->state[0] = dir;
                                        obj->state[1] = col;
                                    }

                                }
                                lua_pop(Lua->L, -1);
                            }
                            if (game_map){
                                if (canrun)
                                    obj->setXY(x,y);
                            }else{
                                obj->setXY(x,y);
                            }
                        }else{
                            if (game_map){
                                game_map->getMap()->moveObjById(obj,x,y,true);
                            }else{
                                obj->setXY(x,y);
                            }
                        }

                    }
                 }
             }
             if (deleted){
                deleted = false;
                break;
             }
             obj = obj->next;
        }
    return 0;
}

int game_loop(){
        if( lua.get_ticks() > MIN_TICK_LUA ) {
            lua.start();
            lua_getglobal(Lua->L, "Game");
            lua_getfield(Lua->L, -1, "mainLoop");
            if (lua_pcall(Lua->L, 0, 0, 0) != 0){
                char *s = (char*)lua_tostring(Lua->L, -1);
                if (consolemain)
                    consolemain->print(s);
                output->write(s);
            }
            lua_pop(Lua->L, -1);
        }
        return 0;
}
#include <stdio.h>
void runIntro(SDL_Event *event);
int main(int argc, char* args[])
{
    output = new Log((char*)"log.log");

    output->write((char*)"Iniciado!\n");

    srand(time(NULL));
    // Initialize the SDL

    /*Start Lua */
    Lua = new luaScript();
    output->write((char*)"Lua started\n");

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        exit(1);
    }
    output->write((char*)"Video started\n");

    //Load images by config.lua
    lua_getglobal(Lua->L, (char*)"IMAGES_MAX");
    IMAGES_MAX = lua_tonumber(Lua->L,1);
    lua_pop(Lua->L,-1);



    output->write((char*)"Loading images by config\n");
    surfaceList = (SDL_Surface**)malloc(sizeof(SDL_Surface*)*IMAGES_MAX);
    for (int i=0;i<IMAGES_MAX;i++)
        surfaceList[i] = NULL;

    lua_getglobal(Lua->L, (char*)"IMAGES");
    lua_pushnil(Lua->L);

    while( lua_next( Lua->L, -2 ) ) {
    	if( lua_isstring( Lua->L, -1 ) ) {
    		char *jdej = (char*)lua_tostring( Lua->L, -1 );
    		char ss[90];
    		sprintf(ss,"Load: %s\n",jdej);
    		output->write(ss);
    		IMG_Load_ENGINE(jdej);
    	}
    	lua_pop( Lua->L, 1 );
    }
    lua_pop( Lua->L, 1 );

    output->write((char*)"All images have been load.\n");
    lua_getglobal(Lua->L, (char*)"SCREEN_Width");
    SCREEN_Width = lua_tonumber(Lua->L,1);
    lua_pop(Lua->L,-1);
    lua_getglobal(Lua->L, (char*)"SCREEN_Height");
    SCREEN_Height = lua_tonumber(Lua->L,1);
    lua_pop(Lua->L,-1);
    int MAXFPS_I = MAXFPS;
    lua_getglobal(Lua->L, (char*)"LIMIT_FPS");
    MAXFPS_I = lua_tonumber(Lua->L,1);
    lua_pop(Lua->L,-1);
    display = SDL_SetVideoMode(SCREEN_Width, SCREEN_Height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (display == NULL)
    {
        exit(1);
    }
    output->write((char*)"Display set\n");
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ) {
            exit(1);
    }
    Mix_AllocateChannels(NUMCHANNELS);

    SDL_WM_SetCaption((char*)"Unamed =]", (char*)"Sem nome");
    /*Start text interface */
    TTF_Init();

    /*Objeto e efeitos mãe */
    mother = createObject((char*)"$0",0.1f,0.1f);  //Mother! Objeto inativo.               ESTTICO
    (new Effect((char*)"$1",100,100,2,4,235,146,250,true,0))->frameskip = -1; //Efeito inativo    ESTTICO



    output->write((char*)"Set all mothers.\n");
    /* Console */

    consolemain = new Console(10,10,20);
    output->write((char*)"Console ON!\n");

    Lua->startEngine();
    output->write((char*)"Lua started engine\n");

    /* Start input*/

    user = new User();
    output->write((char*)"User created\n");
    SDL_Event event;

    /* Introdução */
    output->write((char*)"Intro?\n");
    output->write((char*)"Intro ok\n");
    //Objetos padrão

    output->write((char*)"K....\n");
    //game_map = new Map((char*)"$11",(char*)"");
    output->write((char*)"Map load done\n");

    /*Particles!*/

    last_part = mother_part = new Particle(100.0,100.0,30,0);
    mother_part->enable();
    mother_part->ef_type = CIRCLE_EF;
    mother_part->blink = true;
    mother_part->fade = true;
    mother_part->maxSteps = 80;

    output->write((char*)"Particles started.\n");


    float xe[] = {32};
    float ye[] = {32};
    (new Polygon(xe,ye,1,POLY_PIXEL))->setColor(255,0,0);

    /* Multi threads */
    Objeto *trocador,*top[50];
    int topn=0;
    update.start(); //Calculo do FPS real

    int frame = 0;
    lua.start();


    SDL_Surface *ss = (SDL_Surface *)malloc(sizeof(SDL_Surface));
    ss->h = 100;
    ss->w = 100;

    //
    inputs.start();
    output->write((char*)"Begin envoriment.\n");
    Lua->beginEnvoriment();
    output->write((char*)"Started game.\n");

    while(1){
        fps.start(); //Timer para regular o FPS
        SDL_FillRect( display, &display->clip_rect, SDL_MapRGB( display->format, BACKGROUND_COLOR ) );
        topn = 0;
        //Limpar a tela

        /* Renderização */
        if (game_map){
            game_map->render(display);
        }

        trocador = mother;
        while(trocador != NULL){ //Usando lista
            if (trocador->alive){
                if (trocador->onTop){
                    top[topn] = trocador;
                    topn++;
                }else{
                    if (trocador->getType() != OBJ_MAP && trocador != mother)
                    trocador->render(display);
                }
            }else{
                deleted = false;
                delete trocador;
                break;
            }
            trocador = trocador->next;
        }

        //Renderizar efeitos
        Effect *swt = (Effect*)mother_ef,*prev;
        if (swt != NULL){ //Lista!
            while(swt != NULL){
                if (swt != mother_ef)
                    swt->show(display);
                prev = swt;
                swt = (Effect*)swt->next;
                if(!prev->alive){
                      delete prev;
                }
            }
        }
        int fff = 0;
        for (fff=0;fff<topn;fff++){
            if (!top[fff]->alive)
                    break;
            top[fff]->render(display);
        }

        Polygon *pl = mother_pol;
        if (pl != NULL){ //Lista!
            while(pl != NULL){
                if (pl != mother_pol)
                    pl->render(display);
                pl = pl->next;
                if(pl->isAlive() == false){
                       delete pl;
                }
            }
        }
        Particle *pr = mother_part,*pr0;
        if (pr != NULL){ //Lista!
            while(pr != NULL){
                pr->perform();
                pr0 = pr;
                pr = (Particle*)pr->next;
                if(!pr0->isAlive()){
                       delete (Particle*)pr0;
                }
            }
        }

        //mother_part->runCircle();

        //pol->setColor(rand()%255,rand()%255,rand()%255);
        //pol->setAlpha(rand()%255);

        game_control(mother);
        timer_tr1.start();
        #ifndef MULTITASK
        animate(mother_ef);
        #endif

        SDL_Flip(display);

         /* Limitando FPS */
        if( ( fps.get_ticks() < 1000 / MAXFPS_I ) )
        { //FPS (lazyfoo.net)
            SDL_Delay( ( 1000 / MAXFPS_I ) - fps.get_ticks() );

        }
        frame++;
        game_loop();
        if( update.get_ticks() > 1000 ) {
                //The frame rate as a string// Zerar a lista completa de imagens.

                std::stringstream caption;
                caption << "The unamed (FPS " << frame << ")";

                //Reset the caption
                SDL_WM_SetCaption( caption.str().c_str(), NULL );
                 //Restart the update timer
                update.start();
                frame = 0;

                /* fim lua */
        }
        if (user->parseEvents(&event) == 0){
            finish_him();
        }

    }
    finish_him();
    return 0;
}
void runIntro(SDL_Event *eventa){

    int inte;
    SDL_Rect dest;
    dest.x = static_cast<int>(0);
    dest.y = static_cast<int>(0);
    SDL_Surface* intro = IMG_Load("intro.jpg");
    if (intro != NULL){
        for (inte = 0;inte <= 255;inte++){
            SDL_FillRect( display, &display->clip_rect, SDL_MapRGB( display->format, BACKGROUND_COLOR ) );
            SDL_SetAlpha(intro,SDL_RLEACCEL | SDL_SRCALPHA,inte);
            SDL_BlitSurface(intro, NULL, display, &dest);
            SDL_Flip(display);
            SDL_Delay( 1 );
        }


        for (inte = 0;inte <= 255;inte++){
            SDL_FillRect( display, &display->clip_rect, SDL_MapRGB( display->format, BACKGROUND_COLOR ) );
            SDL_SetAlpha(intro,SDL_RLEACCEL | SDL_SRCALPHA,255-inte);
            SDL_BlitSurface(intro, NULL, display, &dest);
            SDL_Flip(display);
            SDL_Delay( 1 );
        }
        SDL_FreeSurface(intro);
    }
}

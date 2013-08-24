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

#include "keyboard.h"
#include <math.h>
#include "logs.h"
#include "timer.h"



Console *consolemain;
Map *game_map;

extern Log *output;
extern Timer inputs;
float N=0.1f; //NVM test
extern Particle *mother_part;
User::User(){
    for (int i=0;i<SDLK_LAST;i++)
    PRESS[i] = false;
    MOUSE_X = MOUSE_Y = 0;
}

void User::mouseDown(SDL_Event *ev){
    SDL_Event event = *ev;
    if( event.button.button == SDL_BUTTON_LEFT ) {
        MOUSE_X = event.button.x;
        MOUSE_Y = event.button.y;
    }
    /*mother_part->x = MOUSE_X;
    mother_part->y = MOUSE_Y;
    mother_part->updatePosition(true);
    mother_part->reset();
    mother_part->enable();*/
    lua_getglobal(Lua->L, "Input");
    lua_getfield(Lua->L,-1, "Mouse");
    lua_getfield(Lua->L,-1, "Down");
    if(!lua_isfunction(Lua->L,-1))
    {
        if (consolemain)
            consolemain->print((char*)"Input.Mouse.Down not a lua function.");
        lua_pop(Lua->L,-1);
    }else{
        lua_pushnumber(Lua->L, event.button.button);
        int amnt = 0;
        int coliision_press = -1;
        if (game_map)
            for (int k=0;k<9;k++){
                coliision_press = game_map->getMap()->hasBlock(MOUSE_X,MOUSE_Y,k);
                if(coliision_press != 0){
                    lua_pushnumber(Lua->L, coliision_press);
                    amnt++;
                }
            }

        if (lua_pcall(Lua->L, 1+amnt, 1, 0) != 0) {
            if (consolemain)
                consolemain->print((char*)lua_tostring(Lua->L, -1));
            lua_pop(Lua->L, -1);
        }
        lua_pop(Lua->L, -1);
    }

}
void User::mouseUp(SDL_Event *ev){
    SDL_Event event = *ev;
    lua_getglobal(Lua->L, "Input");
    lua_getfield(Lua->L,-1, "Mouse");
    lua_getfield(Lua->L,-1, "Up");
    if(!lua_isfunction(Lua->L,-1))
    {
        if (consolemain)
            consolemain->print((char*)"Input.Mouse.Up not a lua function.");
        lua_pop(Lua->L,-1);
    }else{
        lua_pushnumber(Lua->L, event.button.button);
        if (lua_pcall(Lua->L, 1, 1, 0) != 0) {
            if (consolemain)
                consolemain->print((char*)lua_tostring(Lua->L, -1));
            lua_pop(Lua->L, -1);
        }
        lua_pop(Lua->L, -1);
    }
}
void User::mouseMotion(int x,int y){
    MOUSE_X = x;
    MOUSE_Y = y;
}
void User::keyRelease(SDL_Event *ev,int key){
    PRESS[key] = false;
    lua_getglobal(Lua->L, "Input");
    lua_getfield(Lua->L,-1, "Keyboard");
    lua_getfield(Lua->L,-1, "Release");
    if(!lua_isfunction(Lua->L,-1))
    {

        lua_pop(Lua->L,-1);
    }
    lua_pushnumber(Lua->L, key);
    if (lua_pcall(Lua->L, 1, 1, 0) != 0) {
        if (consolemain)
            consolemain->print((char*)lua_tostring(Lua->L, -1));
    }
    lua_pop(Lua->L, -1);

     /*switch(key){
         case SDLK_LEFT:
            //if (!Play)
              //  break;
            if (PRESS[SDLK_RIGHT] and not PRESS[SDLK_UP]){
                Play->vX = 1.5;
                if (Play->attach){
                    ((Effect*)Play->attach)->setAlive(false);
                    Play->attach = NULL;
                }
                if (Play->attach  == NULL){
                    Effect *mv;
                    mv = new Effect((char*)"$16",rand()%600,rand()%440,4,1,30,27,100,true,1);
                    mv->x_off = -9;
                    mv->attach = Play;
                    Play->attach = (Objeto*)mv;
                }
            }else{
                Play->vX = 0;
            }
            break;
         case SDLK_RIGHT:
            if (!Play)
                break;
            if (PRESS[SDLK_LEFT] and not PRESS[SDLK_UP]){
                Play->vX = -1.5;
                if (Play->attach){
                    ((Effect*)Play->attach)->setAlive(false);
                    Play->attach = NULL;
                }
                if (Play->attach  == NULL){
                    Effect *mv;
                    mv = new Effect((char*)"$15",rand()%600,rand()%440,4,1,30,27,100,true,1);
                    mv->attach = Play;
                    Play->attach = (Objeto*)mv;
                }
            }else{
                if (!Play)
                    break;
                Play->vX = 0;
            }
            break;
     }*/

}
Objeto *jaaje;
int User::keyPressed(int key){
    PRESS[key] = true;
    lua_getglobal(Lua->L, "Input");
    lua_getfield(Lua->L,-1, "Keyboard");
    lua_getfield(Lua->L,-1, "Press");
    if(lua_isfunction(Lua->L,-1) == 0)
    {
        output->write((char*)"--Input.Keyboard.Press not a lua function.\n");
        lua_pop(Lua->L,-1);
        return -1;
    }
    lua_pushnumber(Lua->L, key);

    if (lua_pcall(Lua->L, 1, 0, 0) != 0) {
        char *err = (char*)lua_tostring(Lua->L, -1);
        if (consolemain)
            consolemain->print(err);
        char ss[80];
        sprintf(ss,"-- Error: %s",err);
        output->write(ss);
        lua_pop(Lua->L, -1);
        return -1;
    }
    lua_pop(Lua->L, 1);

    /*switch(key){
        case SDLK_DELETE:
            delete jaaje;
            break;
        case SDLK_INSERT:
            jaaje = createObject((char*)"$0",20,20);
            break;
        case SDLK_ESCAPE:
            return 0;
        case SDLK_UP:
            if (!Play)
                break;

            Play->tY = -3;

            Play->setVisible(false);
            if (Play->attach){
                ((Effect*)Play->attach)->setAlive(false);
                Play->attach = NULL;
            }
            if (Play->attach  == NULL){
                Effect *mv;
                mv = new Effect((char*)"$17",rand()%600,rand()%440,4,1,30,27,100,true,1);
                mv->attach = Play;
                Play->attach = (Objeto*)mv;
                mv->x_off = -9;
            }
            break;
        case SDLK_DOWN:
            if (!Play)
                break;
            Play->setVisible(false);
            if (Play->attach  == NULL){
                Effect *mv;
                mv = new Effect((char*)"$5",rand()%600,rand()%440,5,4,64,64,20,true,1);
                mv->attach = Play;
                Play->attach = (Objeto*)mv;

            }

            break;
        case SDLK_LEFT:
            if (!Play)
                break;
            Play->setVisible(false);
            if (Play->attach){
                ((Effect*)Play->attach)->setAlive(false);
                Play->attach = NULL;
            }
            if (Play->attach  == NULL){
                Effect *mv;
                mv = new Effect((char*)"$15",rand()%600,rand()%440,4,1,30,27,100,true,1);
                mv->attach = Play;
                Play->attach = (Objeto*)mv;

            }
            Play->vX = -1.5;
            break;
        case SDLK_RIGHT:
            if (!Play)
                break;
            Play->setVisible(false);
            if (Play->attach){
                ((Effect*)Play->attach)->setAlive(false);
                Play->attach = NULL;
            }
            if (Play->attach  == NULL){
                Effect *mv;
                mv = new Effect((char*)"$16",rand()%600,rand()%440,4,1,30,27,100,true,1);
                mv->attach = Play;
                mv->x_off = -9;
                Play->attach = (Objeto*)mv;
            }
            Play->vX = 1.5;
            break;
        }*/
        return 1;
    }


void User::whileKeyPressed(SDL_Event *ev){
    /*if (Play and Play->attach != NULL && (!PRESS[SDLK_UP] && !PRESS[SDLK_DOWN] && !PRESS[SDLK_LEFT] && !PRESS[SDLK_RIGHT]) ){
        Play->setVisible(true);
        ((Effect*)Play->attach)->setAlive(false);
        Play->attach = NULL;
    }*/
   /* if (PRESS[SDLK_SPACE]){
        int r = rand()%70;
        if (r <= 10 && r >= 0){
            new Effect((char*)"$4",rand()%600,rand()%400,10,4,93,100,50,false,1);
        }else if (r <= 20 && r >= 10){
           new Effect((char*)"$3",rand()%600,rand()%440,5,5,64,64,20,false,0);
        }else if (r <= 30 && r >= 20){
           new Effect((char*)"$7",rand()%600,rand()%400,8,4,64,64,20,false,1);
        }else if (r <= 40 && r >= 30){
           new Effect((char*)"$6",rand()%600,rand()%400,8,4,64,64,20,false,1);
        }else if (r <= 50 && r >= 40){
           new Effect((char*)"$5",rand()%600,rand()%400,8,4,64,64,20,false,1);
        }else if (r <= 60 && r >= 50){
           new Effect((char*)"$8",rand()%600,rand()%400,8,4,64,64,20,false,1);
        }else if (r <= 70 && r >= 60){
           new Effect((char*)"$9",rand()%600,rand()%400,8,4,64,64,20,false,1);
        }
    }*/
}
int User::parseEvents(SDL_Event *ev){ //Função para controlar o teclado
    SDL_Event event = *ev;
    char ss[50];
    while (SDL_PollEvent(&event))
    {
        sprintf(ss,"I have a event to parse [%d]\n",event.type);
        output->write(ss);
        if (event.type == SDL_QUIT)
        {
                return 0;
        }else if( event.type == SDL_MOUSEBUTTONDOWN ){
            output->write((char*)"-Mouse down\n");
            mouseDown(&event);
        }else if( event.type == SDL_MOUSEBUTTONUP ){
            output->write((char*)"-Mouse Up\n");
            mouseUp(&event);
        }else if( event.type == SDL_MOUSEMOTION ){
            mouseMotion(event.motion.x <= 0 ? 0 : (event.motion.x >= 3000 ?  3000 : event.motion.x),event.motion.y <= 0 ? 0 : (event.motion.y >3000 ? 3000 : event.motion.y));
        }else if(event.type == SDL_KEYDOWN){
            output->write((char*)"-Key press\n");
            if (inputs.get_ticks() >= 500 and keyPressed(event.key.keysym.sym) == 0)
              return 0;
        }else if(event.type == SDL_KEYUP){
            output->write((char*)"-Key release\n");
            keyRelease(&event,event.key.keysym.sym);
        }
    }
    whileKeyPressed(&event);
    return 1;
}

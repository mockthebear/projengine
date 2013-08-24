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

#include <iostream>
#include "luascript.h"
#include "console.h"
#include "keyboard.h"
#include "logs.h"
#include "lua.hpp"
#include "polygon.h"
#include "definitions.h"
#include "particles.h"
#include "sound.h"
extern Log *output;
bool registeredType[1024];
extern Console *consolemain;
User *user;
extern bool deleted;
extern Map *game_map;

int32_t luaScript::print_console(lua_State *L){
    if (consolemain)
        consolemain->print((char*)lua_tostring(L, -1));
    lua_pushboolean(L,true);
    return 1;
}
int32_t luaScript::getOS(lua_State *L){
    #ifdef __linux__
    lua_pushstring(L,"unix");
    #elif _WIN32
    lua_pushstring(L,"win");
    #else
    exit(20);
    #endif

    return 1;
}
int32_t luaScript::print_log(lua_State *L){
    char ms[300];
    sprintf((char*)"Lua: %s",lua_tostring(L, -1));
    output->fwrite(ms);
    lua_pushboolean(L,true);
    return 1;
}
int32_t luaScript::setEffectAttachOffsetY(lua_State *L){
    float x = lua_tonumber(L, -1);
    lua_pop(L,1);
    Effect *ef = (Effect *)lua_touserdata(L, -1);
    if (ef != NULL){
          ef->y_off = x;
          lua_pushboolean(L,true);
    }else{
            lua_pushboolean(L,false);
    }
    return 1;
}
int32_t luaScript::setEffectAttachOffsetX(lua_State *L){
    float x = lua_tonumber(L, -1);
    lua_pop(L,1);
    Effect *ef = (Effect *)lua_touserdata(L, -1);
    if (ef != NULL){
          ef->x_off = x;
          lua_pushboolean(L,true);
    }else{
            lua_pushboolean(L,false);
    }
    return 1;
}
int32_t luaScript::setX(lua_State *L){
    int x = lua_tonumber(L, -1);
    lua_pop(L,1);
    int id = lua_tonumber(L, -1);
    Objeto * bj = getObjectById(id);
    if (bj != NULL){
          bj->setX(x);
          lua_pushboolean(L,true);
    }else{
            lua_pushboolean(L,false);
    }
    return 1;
}
int32_t luaScript::setVisible(lua_State *L){
    bool x = lua_toboolean(L, -1);
    lua_pop(L,1);
    int id = lua_tonumber(L, -1);
    Objeto * bj = getObjectById(id);
    if (bj != NULL){
          bj->setVisible(x);
          lua_pushboolean(L,true);
    }else{
            lua_pushboolean(L,false);
    }
    return 1;
}

int32_t luaScript::setAttachF(lua_State *L){
    int id = lua_tonumber(L, -1);
    Objeto * bj = getObjectById(id);
    lua_pop(L,1);
    Effect *ef = (Effect *)lua_touserdata(L, -1);
    if (bj != NULL and ef != NULL){
          ef->attach = (Base*)bj;
          lua_pushboolean(L,true);
    }else{
            lua_pushboolean(L,false);
    }
    return 1;
}
int32_t luaScript::setAttach(lua_State *L){
    Effect *ef = (Effect *)lua_touserdata(L, -1);
    lua_pop(L,1);
    int id = lua_tonumber(L, -1);
    Objeto * bj = getObjectById(id);
    if (bj != NULL){
          bj->attach = (Base*)ef;
          lua_pushboolean(L,true);
    }else{
            lua_pushboolean(L,false);
    }
    return 1;
}
int32_t luaScript::setAlive(lua_State *L){
    bool x = lua_toboolean(L, -1);
    lua_pop(L,1);
    Effect *ef = (Effect *)lua_touserdata(L, -1);
    if (ef != NULL){
          ef->setAlive(x);
          lua_pushboolean(L,true);
    }else{
            lua_pushboolean(L,false);
    }
    return 1;
}
int32_t luaScript::setgY(lua_State *L){
    float x = lua_tonumber(L, -1);
    lua_pop(L,1);
    int id = lua_tonumber(L, -1);
    Objeto * bj = getObjectById(id);
    if (bj != NULL){
          bj->gY = x;
          lua_pushboolean(L,true);
    }else{
            lua_pushboolean(L,false);
    }
    return 1;
}
int32_t luaScript::setVy(lua_State *L){
    float x = lua_tonumber(L, -1);
    lua_pop(L,1);
    int id = lua_tonumber(L, -1);
    Objeto * bj = getObjectById(id);
    if (bj != NULL){
          bj->vY = x;
          lua_pushboolean(L,true);
    }else{
            lua_pushboolean(L,false);
    }
    return 1;
}
int32_t luaScript::setStack(lua_State *L){
    int x = lua_tonumber(L, -1);
    lua_pop(L,1);
    int id = lua_tonumber(L, -1);
    Objeto * bj = getObjectById(id);
    if (bj != NULL){
          bj->stack = x;
          lua_pushboolean(L,true);
    }else{
            lua_pushboolean(L,false);
    }
    return 1;
}
int32_t luaScript::setVx(lua_State *L){
    float x = lua_tonumber(L, -1);
    lua_pop(L,1);
    int id = lua_tonumber(L, -1);
    Objeto * bj = getObjectById(id);
    if (bj != NULL){
          bj->vX = x;
          lua_pushboolean(L,true);
    }else{
            lua_pushboolean(L,false);
    }
    return 1;
}
int32_t luaScript::setType(lua_State *L){
    int x = lua_tonumber(L, -1);
    lua_pop(L,1);
    int id = lua_tonumber(L, -1);
    Objeto * bj = getObjectById(id);
    if (bj != NULL){
          bj->setType(x);
          lua_pushboolean(L,true);
    }else{
            lua_pushboolean(L,false);
    }
    return 1;
}
int32_t luaScript::smoothObject(lua_State *L){
    double a = lua_tonumber(L, -1);
    lua_pop(L,1);
    Base *pp = (Base *)lua_touserdata(L, -1);
    if (pp->CTYPE == EFFECT_){
        Effect  *e = (Effect*)pp;
        e->flip(0,1,a);
        lua_pushboolean(L,true);
    }else if(pp->CTYPE == OBJ){
        Objeto *e = (Objeto*)pp;
        e->flip(0,1,a);
        lua_pushboolean(L,true);
    }else{
        lua_pushboolean(L,false);
    }
    return 1;
}
int32_t luaScript::ampliateObject(lua_State *L){
    double a = lua_tonumber(L, -1);
    lua_pop(L,1);
    Base *pp = (Base *)lua_touserdata(L, -1);
    if (pp->CTYPE == EFFECT_){
        Effect  *e = (Effect*)pp;
        e->flip(0,a,0);
        lua_pushboolean(L,true);
    }else if(pp->CTYPE == OBJ){
        Objeto *e = (Objeto*)pp;
        e->flip(0,a,0);
        lua_pushboolean(L,true);
    }else{
        lua_pushboolean(L,false);
    }
    return 1;
}
int32_t luaScript::flipObject(lua_State *L){
    double a = lua_tonumber(L, -1);
    lua_pop(L,1);
    Base *pp = (Base *)lua_touserdata(L, -1);
    if (pp->CTYPE == EFFECT_){
        Effect  *e = (Effect*)pp;
        e->flip(a,1,0);
        lua_pushboolean(L,true);
    }else if(pp->CTYPE == OBJ){
        Objeto *e = (Objeto*)pp;
        e->flip(a,1,0);
        lua_pushboolean(L,true);
    }else{
        lua_pushboolean(L,false);
    }
    return 1;
}
int32_t luaScript::setY(lua_State *L){
    int y = lua_tonumber(L, -1);
    lua_pop(L,1);
    int id = lua_tonumber(L, -1);
    Objeto * bj = getObjectById(id);
    if (bj != NULL){
          bj->setY(y);
          lua_pushboolean(L,true);
    }else{
            lua_pushboolean(L,false);
    }
    return 1;
}


int32_t luaScript::setText(lua_State *L){
    char* nome = (char*)lua_tostring(L, -1);
    lua_pop(L,1);
    int id = lua_tonumber(L, -1);
    Objeto * bj = getObjectById(id);
    if (bj != NULL){
          bj->setText(nome);
    }else{
            lua_pushboolean(L,false);
    }
    return 1;
}

int32_t luaScript::setFont(lua_State *L){
    int sz = lua_tonumber(L, -1);
    lua_pop(L,1);
    char* nome = (char*)lua_tostring(L, -1);
    lua_pop(L,1);
    int id = lua_tonumber(L, -1);
    Objeto * bj = getObjectById(id);
    if (bj != NULL){
          bj->setFont(nome,sz);
    }else{
            lua_pushboolean(L,false);
    }
    return 1;
}


int32_t luaScript::setTY(lua_State *L){
    int y = lua_tonumber(L, -1);
    lua_pop(L,1);
    int id = lua_tonumber(L, -1);
    Objeto * bj = getObjectById(id);
    if (bj != NULL){
          bj->tY = y;
          lua_pushboolean(L,true);
    }else{
            lua_pushboolean(L,false);
    }
    return 1;
}

int32_t luaScript::createPolygon(lua_State *L){
        int type = lua_tonumber( L, -1 );
        lua_pop( L, 1 );
        float vvx[60],vvy[60];
        int n=0;
        lua_pushnil(L);
        int pred;
        while(lua_next( L, -2 )){
            pred = (int)lua_tonumber( L, -1 );
            vvy[n] = pred;
            n++;
            lua_pop( L, 1 );

        }
        lua_pop( L, 1 );
        lua_pushnil(L);
        n = 0;
        while(lua_next( L, -2 )){
            pred = (int)lua_tonumber( L, -1 );
            vvx[n] = pred;
            n++;
            lua_pop( L, 1 );

        }
        lua_pushlightuserdata (L, (new Polygon(vvx,vvy,n,type)));


    return 1;
}

int32_t luaScript::getObjectStateId(lua_State *L){
    int i = lua_tonumber(L, -1);
    i = i < 0 ? 0 : i;
    i = i > 9 ? 9 : i;
    lua_pop(L,1);
    int id = lua_tonumber(L, -1);
    Objeto * bj = getObjectById(id);
    if (bj != NULL and id != 0){
          lua_pushnumber(L,bj->state[i]);
    }else{
            lua_pushboolean(L,false);
    }
    return 1;
}





int32_t luaScript::getY(lua_State *L){
    int id = lua_tonumber(L, -1);
    Objeto * bj = getObjectById(id);
    if (bj != NULL){
          lua_pushinteger(L,bj->getY());
    }else{
            lua_pushboolean(L,false);
    }
    return 1;
}
int32_t luaScript::getX(lua_State *L){
    int id = lua_tonumber(L, -1);
    Objeto * bj = getObjectById(id);
    if (bj != NULL){
          lua_pushinteger(L,bj->getX());
    }else{
            lua_pushboolean(L,false);
    }
    return 1;
}
int32_t luaScript::getAttach(lua_State *L){
    int id = lua_tonumber(L, -1);
    Objeto * bj = getObjectById(id);
    if (bj != NULL and bj->attach != NULL){
        lua_pushlightuserdata (L, bj->attach);
    }else{
        lua_pushboolean(L,false);
    }
    return 1;
}
int32_t luaScript::getW(lua_State *L){
    int id = lua_tonumber(L, -1);
    Objeto * bj = getObjectById(id);
    if (bj != NULL){
          lua_pushinteger(L,bj->getImage()->w);
    }else{
            lua_pushboolean(L,false);
    }
    return 1;
}
int32_t luaScript::getH(lua_State *L){
    int id = lua_tonumber(L, -1);
    Objeto * bj = getObjectById(id);
    if (bj != NULL){
          lua_pushinteger(L,bj->getImage()->h);
    }else{
            lua_pushboolean(L,false);
    }
    return 1;
}

int32_t luaScript::getMouseX(lua_State *L){
    lua_pushinteger(L,user->MOUSE_X);
    return 1;
}
int32_t luaScript::getMouseY(lua_State *L){
    lua_pushinteger(L,user->MOUSE_Y);
    return 1;
}
int32_t luaScript::setObjectPosition(lua_State *L){
    int y = lua_tonumber(L, -1);
    lua_pop(L,1);
    int x = lua_tonumber(L, -1);
    lua_pop(L,1);
    int id = lua_tonumber(L, -1);

    Objeto * bj = getObjectById(id);
    if (bj != NULL and game_map){
            if (bj->stack == -1){
                bj->setXY(x,y);
            }else{
                    lua_pushboolean(L,game_map->getMap()->moveObjById(bj,x,y,false));
            }
    }else{
            char jaj[54];
            sprintf(jaj,"Cannot find object id %d",id);
            if (consolemain)
                consolemain->print(jaj);
            lua_pushboolean(L,false);
    }
    return 1;
}
int32_t luaScript::setEnableConsole(lua_State *L){
    if (consolemain)
        consolemain->enabled = lua_toboolean(L, -1);
    return 0;
}
int32_t luaScript::createEffect(lua_State *L){
    bool loop = lua_toboolean(L, -1);
    lua_pop(L,1);
    int delay = lua_tonumber(L, -1);
    lua_pop(L,1);
    int sizey = lua_tonumber(L, -1);
    lua_pop(L,1);
    int sizex = lua_tonumber(L, -1);
    lua_pop(L,1);
    int yamount = lua_tonumber(L, -1);
    lua_pop(L,1);
    int xamount = lua_tonumber(L, -1);
    lua_pop(L,1);
    int y = lua_tonumber(L, -1);
    lua_pop(L,1);
    int x = lua_tonumber(L, -1);
    lua_pop(L,1);
    char* nome = (char*)lua_tostring(L, -1);

    lua_pushlightuserdata (L, new Effect(nome ,x,y,xamount,yamount,sizex,sizey,delay,loop,0));

    return 1;
}
int32_t luaScript::deleteObject(lua_State *L){
    int id = lua_tonumber(L, -1);
    lua_pop(L,1);
    Objeto * bj = getObjectById(id);
    if (bj != NULL){
        char ss[50];
        sprintf(ss,"Deleting id %d\n",id);
        output->write(ss);
        if (game_map)
            game_map->getMap()->clearId(bj->id);
        delete bj;
        lua_pushboolean(L,true);
    }else{
        lua_pushboolean(L,false);
    }
    return 1;
}

int32_t luaScript::delete_(lua_State *L){
    void *u = lua_touserdata(L, -1);
    switch(((Base*)u)->CTYPE){ //Unsecure but ok.
    case OBJ:
        delete (Objeto*)u;
        break;
    case EFFECT_:
        delete ((Effect*)u);
        break;
    case POLYGON:
        delete (Polygon*)u;
        break;
    case PARTICLE:
        delete (Particle*)u;
        break;
    case SOUND:
        delete (Sound*)u;
        break;
    }
    return 0;
}

int32_t luaScript::getCollisionPointS(lua_State *L){
    if (!game_map){
        lua_pushboolean(L,false);
    }else{
        int s = lua_tonumber(L, -1);
        lua_pop(L,1);
        int y = lua_tonumber(L, -1);
        lua_pop(L,1);
        int x = lua_tonumber(L, -1);
        lua_pushnumber(L,game_map->getMap()->hasBlock(x,y,s));
    }
    return 1;
}
int32_t luaScript::getCollisionPoint(lua_State *L){
    if (!game_map){
        lua_pushboolean(L,false);
    }else{
        int y = lua_tonumber(L, -1);
        lua_pop(L,1);
        int x = lua_tonumber(L, -1);
        lua_pushnumber(L,game_map->getMap()->hasBlock(x,y));
    }
    return 1;
}
int32_t luaScript::setPolygonColor(lua_State *L){

        int b = lua_tonumber(L, -1);
        lua_pop(L,1);
        int g = lua_tonumber(L, -1);
        lua_pop(L,1);
        int r = lua_tonumber(L, -1);
        lua_pop(L,1);
        Polygon *pp = (Polygon *)lua_touserdata(L, -1);
        lua_pop(L,1);
        if (pp != NULL){
            pp->setColor(r,g,b);
            lua_pushboolean(L,true);
        }else{
            lua_pushboolean(L,false);
        }

    return 1;
}
int32_t luaScript::movePolygonXY(lua_State *L){
        int y= lua_tonumber(L, -1);
        lua_pop(L,1);
        int x = lua_tonumber(L, -1);
        lua_pop(L,1);
        Polygon *pp = (Polygon *)lua_touserdata(L, -1);
        lua_pop(L,1);
        if (pp != NULL){
            pp->moveXAll(x);
            pp->moveYAll(y);
            lua_pushboolean(L,true);
        }else{
            lua_pushboolean(L,false);
        }

    return 1;
}

int32_t luaScript::setPolygonAlpha(lua_State *L){


        int r = lua_tonumber(L, -1);
        lua_pop(L,1);
        Polygon *pp = (Polygon *)lua_touserdata(L, -1);
        lua_pop(L,1);
        if (pp != NULL){
            pp->setAlpha(r);
            lua_pushboolean(L,true);
        }else{
            lua_pushboolean(L,false);
        }

    return 1;
}

int32_t luaScript::setTextColor(lua_State *L){

        int b = lua_tonumber(L, -1);
        lua_pop(L,1);
        int g = lua_tonumber(L, -1);
        lua_pop(L,1);
        int r = lua_tonumber(L, -1);
        lua_pop(L,1);
        int id = lua_tonumber(L, - 1);
        lua_pop(L,1);
        Objeto * bj = getObjectById(id);
        if (bj != NULL){
            bj->setTextColor(r,b,g);
            lua_pushboolean(L,true);
        }else{
            lua_pushboolean(L,false);
        }

    return 1;
}
int32_t luaScript::setCollisionAreaS(lua_State *L){
    if (!game_map){
        lua_pushboolean(L,false);
    }else{
        int S = lua_tonumber(L, -1);
        lua_pop(L,1);
        int type = lua_tonumber(L, -1);
        lua_pop(L,1);
        int yamount = lua_tonumber(L, -1);
        lua_pop(L,1);
        int xamount = lua_tonumber(L, -1);
        lua_pop(L,1);
        int y = lua_tonumber(L, -1);
        lua_pop(L,1);
        int x = lua_tonumber(L, -1);
        lua_pop(L,1);
        game_map->getMap()->setCollisionArea(x,y,xamount,yamount,type,S);

        lua_pushboolean(L,true);
    }
    return 1;
}
int32_t luaScript::setCollisionArea(lua_State *L){
    if (!game_map){
        lua_pushboolean(L,false);
    }else{
        int type = lua_tonumber(L, -1);
        lua_pop(L,1);
        int yamount = lua_tonumber(L, -1);
        lua_pop(L,1);
        int xamount = lua_tonumber(L, -1);
        lua_pop(L,1);
        int y = lua_tonumber(L, -1);
        lua_pop(L,1);
        int x = lua_tonumber(L, -1);
        lua_pop(L,1);
        game_map->getMap()->setCollisionArea(x,y,xamount,yamount,type);

        lua_pushboolean(L,true);
    }
    return 1;
}
int32_t luaScript::loadLevel(lua_State *L){
    if (game_map){
        lua_pushboolean(L,false);
    }else{
        char* nome = (char*)lua_tostring(L, -1);
        lua_pop(L,-1);
        char* bkg = (char*)lua_tostring(L, 0);
        game_map = new Map(bkg,nome);
        lua_pushlightuserdata (L,game_map);
    }
    return 1;
}
int32_t luaScript::unloadLevel(lua_State *L){
    if (game_map){

        delete game_map;
        game_map = NULL;
        lua_pushboolean(L,true);
    }else{
        lua_pushboolean(L,false);
    }
    return 1;
}
int32_t luaScript::getObjectIdByPointer(lua_State *L){
    Objeto * bj = (Objeto *)lua_touserdata(L, -1);
    if (bj != NULL){
        lua_pushinteger(L, bj->id);
    }else{
            lua_pushboolean(L,false);
    }
    return 1;
}

int32_t luaScript::getTicks(lua_State *L){
    lua_pushinteger(L, SDL_GetTicks());
    return 1;
}

int32_t luaScript::getObjectPointerById(lua_State *L){
    int id = lua_tonumber(L, -1);
    Objeto * bj = getObjectById(id);

    if (bj != NULL){
        lua_pushlightuserdata (L, bj);
    }else{
            lua_pushboolean(L,false);
    }
    return 1;
}
int32_t luaScript::createObject_lua(lua_State *L){
    float y = lua_tonumber(L, -1);
    lua_pop(L,1);
    float x = lua_tonumber(L, -1);
    lua_pop(L,1);
    char *name = (char*)lua_tostring(L, -1);

    Objeto *obj = createObject(name,x,y);
    if (obj != NULL){
        lua_pushinteger(L, obj->id);
    }else{
        lua_pushboolean(L,false);
    }
    return 1;
}

int32_t luaScript::setObjectClips(lua_State *L){
    int h = lua_tonumber(L, -1);
    lua_pop(L,1);
    int w = lua_tonumber(L, -1);
    lua_pop(L,1);
    int y = lua_tonumber(L, -1);
    lua_pop(L,1);
    int x = lua_tonumber(L, -1);
    lua_pop(L,1);
    int id = lua_tonumber(L, -1);
    lua_pop(L,1);

    Objeto * bj = getObjectById(id);
    if (bj != NULL){
        bj->setClips(x,y,h,w);
        lua_pushboolean(L,true);
    }else{
        lua_pushboolean(L,false);
    }
    return 1;
}





void luaScript::loadScript(char *name){
    char ss[50];
    sprintf(ss,"---Letiz lod %s\n",name);
    output->write(ss);
    if (luaL_dofile(L,name) != 0){
        output->write((char*)"---Not workin'\n");
        output->write((char*)lua_tostring(L, -1));
        finish_him();
    }else{
        output->write((char*)"---Workin'\n");
        lua_pop(L,0);
    }
}




Objeto *getObjectById(int id_){
    if (id_ == 0){
        return NULL;
    }
    Objeto *obj = mother;
    while(obj != NULL){
        if (obj->id ==id_){
            return obj;
        }
        if (deleted)
            break;
        obj = obj->next;
    }
    return NULL;
}
int32_t luaScript::registerType(lua_State *L){
    int y = lua_tonumber(L, -1);
    lua_pop(L,1);
    y = y > 1024 ? 1024 : y;
    //Lua->setRegisterState(y,true);
    registeredType[y] = true;
    return 0;
}


int32_t luaScript::setParticleMaxSteps(lua_State *L){
    int x = lua_tonumber(L, -1);
    lua_pop(L,1);
    Particle * pr = (Particle *)lua_touserdata(L, -1);
    lua_pop(L,1);
    if (pr->CTYPE == PARTICLE)
        pr->maxSteps = x;
    return 0;
}


int32_t luaScript::particleReset(lua_State *L){
    Particle * pr = (Particle *)lua_touserdata(L, -1);
    lua_pop(L,1);
    pr->reset();
    return 0;
}

int32_t luaScript::setParticleEffectType(lua_State *L){
    int x = lua_tonumber(L, -1);
    lua_pop(L,1);
    Particle * pr = (Particle *)lua_touserdata(L, -1);
    lua_pop(L,1);
    if (pr->CTYPE == PARTICLE)
        pr->ef_type = x;
    return 0;
}

int32_t luaScript::setEnabledParticle(lua_State *L){
    bool x = lua_toboolean(L, -1);
    lua_pop(L,1);
    Particle * pr = (Particle *)lua_touserdata(L, -1);
    lua_pop(L,1);
    if (pr->CTYPE == PARTICLE){
        if (x)
            pr->enable();
        else
            pr->disable();
    }
    return 0;
}
int32_t luaScript::setEnabledParticleFade(lua_State *L){
    bool x = lua_toboolean(L, -1);
    lua_pop(L,1);
    Particle * pr = (Particle *)lua_touserdata(L, -1);
    lua_pop(L,1);
    if (pr->CTYPE == PARTICLE){
        pr->fade = x;
    }
    return 0;
}


int32_t luaScript::setEnabledParticleBlink(lua_State *L){
    bool x = lua_toboolean(L, -1);
    lua_pop(L,1);
    Particle * pr = (Particle *)lua_touserdata(L, -1);
    lua_pop(L,1);
    if (pr->CTYPE == PARTICLE){
        pr->blink = x;
    }
    return 0;
}
int32_t luaScript::loadSound(lua_State *L){
    int x = lua_tonumber(L, -1);
    lua_pop(L,1);
    Sound *sond = new Sound((char*)lua_tostring(L,-1),x);
    lua_pop(L,1);
    if (sond != NULL){
        lua_pushlightuserdata (L, sond);
    }else{
            lua_pushboolean(L,false);
    }

    return 1;
}
int32_t luaScript::resumeMusic(lua_State *L){
    Sound * snd = (Sound *)lua_touserdata(L, -1);
    lua_pop(L,1);
    if (snd->CTYPE == SOUND){
        snd->resume();
    }
    return 0;
}
int32_t luaScript::stopMusic(lua_State *L){
    Sound * snd = (Sound *)lua_touserdata(L, -1);
    lua_pop(L,1);
    if (snd->CTYPE == SOUND){
        snd->stop();
    }
    return 0;
}
int32_t luaScript::pauseMusic(lua_State *L){
    Sound * snd = (Sound *)lua_touserdata(L, -1);
    lua_pop(L,1);
    if (snd->CTYPE == SOUND){
        snd->pause();
    }
    return 0;
}int32_t luaScript::playMusic(lua_State *L){
    Sound * snd = (Sound *)lua_touserdata(L, -1);
    lua_pop(L,1);
    if (snd->CTYPE == SOUND){
        snd->play();
    }
    return 0;
}
int32_t luaScript::soundFadeIn(lua_State *L){
    int z = lua_tonumber(L, -1);
    lua_pop(L,1);
    int y = lua_tonumber(L, -1);
    lua_pop(L,1);
    int x = lua_tonumber(L, -1);
    lua_pop(L,1);
    Sound * snd = (Sound *)lua_touserdata(L, -1);
    lua_pop(L,1);
    if (snd->CTYPE == SOUND){
        snd->playFadeIn(x, y, z);
    }
    return 0;
}
int32_t luaScript::setPositionSound(lua_State *L){
    float y = lua_tonumber(L, -1);
    lua_pop(L,1);
    float x = lua_tonumber(L, -1);
    lua_pop(L,1);
    Sound * snd = (Sound *)lua_touserdata(L, -1);
    lua_pop(L,1);
    if (snd->CTYPE == SOUND){
        snd->setPosition(x,y);
    }
    return 0;
}
int32_t luaScript::setSoundVolume(lua_State *L){
    int x = lua_tonumber(L, -1);
    lua_pop(L,1);
    Sound * snd = (Sound *)lua_touserdata(L, -1);
    lua_pop(L,1);
    if (snd->CTYPE == SOUND){
        snd->setVolume(x);
    }
    return 0;
}

int32_t luaScript::soundFadeOut(lua_State *L){
    int x = lua_tonumber(L, -1);
    lua_pop(L,1);
    Sound * snd = (Sound *)lua_touserdata(L, -1);
    lua_pop(L,1);
    if (snd->CTYPE == SOUND){
        snd->stopFadeOut(x);
    }
    return 0;
}

int32_t luaScript::setParticleStorage(lua_State *L){
    float v = lua_tonumber(L, -1);
    lua_pop(L,1);
    int i = lua_tonumber(L, -1);
    lua_pop(L,1);
    Particle * pr = (Particle *)lua_touserdata(L, -1);
    lua_pop(L,1);
    if (pr->CTYPE == PARTICLE){
        pr->setStorage(i,v);
    }
    return 1;
}
int32_t luaScript::setParticleColor(lua_State *L){
    short b = lua_tonumber(L, -1);
    lua_pop(L,1);
    short g = lua_tonumber(L, -1);
    lua_pop(L,1);
    short r = lua_tonumber(L, -1);
    lua_pop(L,1);
    Particle * pr = (Particle *)lua_touserdata(L, -1);
    lua_pop(L,1);
    if (pr->CTYPE == PARTICLE){
        pr->setColor(r,g,b);
    }
    return 1;
}

int32_t luaScript::setParticlePosition(lua_State *L){
    bool b = lua_toboolean(L, -1);
    lua_pop(L,1);
    int y = lua_tonumber(L, -1);
    lua_pop(L,1);
    int x = lua_tonumber(L, -1);
    lua_pop(L,1);
    Particle * pr = (Particle *)lua_touserdata(L, -1);
    lua_pop(L,1);
    if (pr->CTYPE == PARTICLE){
        pr->ox = pr->x;
        pr->oy = pr->y;
        pr->x = x;
        pr->y = y;
        pr->updatePosition(b);
    }
    return 1;
}
int32_t luaScript::createParticleEngine(lua_State *L){
    int s = lua_tonumber(L, -1);
    lua_pop(L,1);
    int id = lua_tonumber(L, -1);
    lua_pop(L,1);
    int y = lua_tonumber(L, -1);
    lua_pop(L,1);
    int x = lua_tonumber(L, -1);
    lua_pop(L,1);
    lua_pushlightuserdata (L, new Particle(x,y,id,s));
    return 1;
}
int32_t luaScript::unregisterType(lua_State *L){
    int y = lua_tonumber(L, -1);
    lua_pop(L,1);
    y = y > 1024 ? 1024 : y;
    //Lua->setRegisterState(y,false);
    registeredType[y] = false;
    return 0;
}

void luaScript::registerFunctions(lua_State *L){


    output->write((char*)"--Register functions\n");
    lua_register(L, "printe", luaScript::print_console);

    //Particles
    lua_register(L, "createParticleEngine", luaScript::createParticleEngine);
    lua_register(L, "setParticleEnabled", luaScript::setEnabledParticle);
    lua_register(L, "setParticleEffectType", luaScript::setParticleEffectType);
    lua_register(L, "setParticleMaxSteps", luaScript::setParticleMaxSteps);
    lua_register(L, "setEnabledParticleFade", luaScript::setEnabledParticleFade);
    lua_register(L, "setParticleColor", luaScript::setParticleColor);
    lua_register(L, "setEnabledParticleBlink", luaScript::setEnabledParticleBlink);
    lua_register(L, "particleReset", luaScript::particleReset);
    lua_register(L, "setParticlePosition", luaScript::setParticlePosition);
    lua_register(L, "setParticleStorage", luaScript::setParticleStorage);

    /*! common */

    //Polygon
    lua_register(L, "createPolygon", luaScript::createPolygon);
    lua_register(L, "setPolygonColor", luaScript::setPolygonColor);
    lua_register(L, "setPolygonAlpha", luaScript::setPolygonAlpha);
    lua_register(L, "movePolygonXY", luaScript::movePolygonXY);


    lua_register(L, "log", luaScript::print_log);
    lua_register(L, "setEnableConsole", luaScript::setEnableConsole);
    lua_register(L, "setObjectPosition", luaScript::setObjectPosition);
    lua_register(L, "getObjectPointerById", luaScript::getObjectPointerById);
    lua_register(L, "getObjectIdByPointer", luaScript::getObjectIdByPointer);
    lua_register(L, "createObject", luaScript::createObject_lua);
    lua_register(L, "setY", luaScript::setY);
    lua_register(L, "setStack", luaScript::setStack);
    lua_register(L, "setTy", luaScript::setTY);
    lua_register(L, "setGy", luaScript::setgY);
    lua_register(L, "setVy", luaScript::setVy);
    lua_register(L, "setVx", luaScript::setVx);
    lua_register(L, "setVisible", luaScript::setVisible);
    lua_register(L, "setType", luaScript::setType);
    lua_register(L, "setFont", luaScript::setFont);
    lua_register(L, "setTextColor", luaScript::setTextColor);


    lua_register(L, "setX", luaScript::setX);
    lua_register(L, "setText", luaScript::setText);
    lua_register(L, "getY", luaScript::getY);
    lua_register(L, "getObjectStateId", luaScript::getObjectStateId);
    lua_register(L, "getX", luaScript::getX);
    lua_register(L, "getAttach", luaScript::getAttach);
    lua_register(L, "setAttach", luaScript::setAttach);

    lua_register(L, "delete", luaScript::delete_);
    lua_register(L, "getH", luaScript::getH);
    lua_register(L, "getTicks", luaScript::getTicks);
    lua_register(L, "getW", luaScript::getW);
    lua_register(L, "getMouseY", luaScript::getMouseY);
    lua_register(L, "getMouseX", luaScript::getMouseX);
    lua_register(L, "deleteObject", luaScript::deleteObject);
    lua_register(L, "registerType", luaScript::registerType);
    lua_register(L, "unregisterType", luaScript::unregisterType);
    lua_register(L, "createEffect", luaScript::createEffect);

    //Sprite
    lua_register(L, "rotateSprite", luaScript::flipObject);
    lua_register(L, "ampliateSprite", luaScript::ampliateObject);
    lua_register(L, "smoothSprite", luaScript::smoothObject);

    //Sound

    lua_register(L, "loadSound", luaScript::loadSound);
    lua_register(L, "soundFadeOut", luaScript::soundFadeOut);
    lua_register(L, "soundFadeIn", luaScript::soundFadeIn);
    lua_register(L, "playSound", luaScript::playMusic);
    lua_register(L, "pauseSound", luaScript::pauseMusic);
    lua_register(L, "stopSound", luaScript::pauseMusic);
    lua_register(L, "resumeSound", luaScript::resumeMusic);
    lua_register(L, "setSoundVolume", luaScript::setSoundVolume);
    lua_register(L, "setPositionSound", luaScript::setPositionSound);



    //Effect:

    lua_register(L, "setAlive", luaScript::setAlive);
    lua_register(L, "setEffectAttachOffsetX", luaScript::setEffectAttachOffsetX);
    lua_register(L, "setEffectAttachOffsetY", luaScript::setEffectAttachOffsetY);
    lua_register(L, "setAttachF", luaScript::setAttachF);

    //Level

    lua_register(L, "unloadLevel", luaScript::unloadLevel);
    lua_register(L, "loadLevel", luaScript::loadLevel);

    //Collision

    lua_register(L, "setCollisionArea", luaScript::setCollisionArea);
    lua_register(L, "setCollisionAreaS", luaScript::setCollisionAreaS);
    lua_register(L, "getCollisionPoint", luaScript::getCollisionPoint);
    lua_register(L, "setObjectClips", luaScript::setObjectClips);
    lua_register(L, "getCollisionPointS", luaScript::getCollisionPointS);


}
void luaScript::startEngine(){
    output->write((char*)"-Starting lua engine.\n");
    int i;
    for (i=0;i<1024;i++){
        registeredType[i] = false;
    }

    registerFunctions(L);

    //lua_register(L, "", luaScript::);

    loadScript((char*)"lua/init.lua");
    output->write((char*)"-Init.lua loaded\n");


    loadScript((char*)"lua/input.lua");
    output->write((char*)"-Input.lua\n");
    output->write((char*)"-Done.\n");
    //Now run
}
luaScript::luaScript(){
    //oi
    L =  lua_open();
    luaL_openlibs(L);
    lua_register(L, "getOS", luaScript::getOS);
    loadScript((char*)"lua/config.lua");
    loadScript((char*)"lualib/lib.lua");


}

luaScript::~luaScript(){
    lua_close(L);
}

void luaScript::beginEnvoriment(){
    output->write((char*)"-Running init\n");
    lua_getglobal(L, "onInit");
    if(lua_isfunction(L,-1) == 0)
    {
        output->write((char*)"-Oh noes! Error! onInit is not a function.\n");
        output->write((char*)lua_tostring(L, -1));
        lua_pop(L,-1);
    }else{
        if (lua_pcall(L, 0, 0,0) != 0){
            char err[200];
            sprintf(err,"-Error: %s",lua_tostring(L, -1));
            output->write(err);
            finish_him();
        }
        lua_pop(L, -1);
    }
    output->write((char*)"-Done\n");
}



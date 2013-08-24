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

#include "imageloader.h"
#include "luascript.h"
#include <math.h>

extern luaScript *Lua;
int Nimgs = 0;

SDL_Surface **surfaceList;
//SDL_Surface *surfaceList[MAX_IMAGES_LOAD];

SDL_Surface* IMG_Load_ENGINE(char *nm){
    surfaceList[Nimgs] =IMG_Load(nm);
    Nimgs++;
    return NULL;
}
int getInt(char *s,int i){
    int out = 0,am[5];
    float ret=0.0;
    while (s[i] != '\0' && s[i] != ';'){
        am[out] = s[i]-48;
        out++;
        i++;
    }
    for (int e=0;e<out;e++){
            ret += ((float) am[e])*pow(10,(out-e)-1);
    }
    return ret;
}
int getNextPV(char *s,int i){
    while (s[i] != '\0' && s[i] != ';'){
        i++;
    }
    return i;
}
SDL_Surface* IMgetImage(char *nome,SDL_Rect *clips,bool *useclip){
    if (nome[0] == '$'){
        return surfaceList[getInt(nome,1)];
    }else if(nome[0] == 'a'){
        // %1;63;63;10;10  //Size 63x63 start at 10 10
        int i = getNextPV(nome,1);
        (*clips).x =getInt(nome,i+1);
        i = getNextPV(nome,i+1);
        (*clips).y = getInt(nome,i+1);
        i = getNextPV(nome,i+1);
        (*clips).w = getInt(nome,i+1);
        i = getNextPV(nome,i+1);
        (*clips).h = getInt(nome,i+1);
        *useclip = true;
        return surfaceList[getInt(nome,1)];
    }else{
        return IMG_Load(nome);
    }
}

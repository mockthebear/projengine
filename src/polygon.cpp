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

#include "polygon.h"
#include <stdlib.h>
#include "SDL_gfxPrimitives.h"

Polygon *mother_pol = NULL,*last_pol = NULL;
Polygon::Polygon(float *vx,float *vy,int na,int ta){
    n = na;
    int i;
    CTYPE = POLYGON;
    xx = (float*)malloc(sizeof(float)*n);
    yy = (float*)malloc(sizeof(float)*n);
    for (i=0;i<n;i++){
        xx[i] = vx[i];
        yy[i] = vy[i];
    }
    t = ta;
    alive = true;
    enable = true;
    r = g = b = a = 255;
    next = prev = NULL;
    if (last_pol != NULL){
        last_pol->next = this;
        prev = last_pol;
    }else{
        mother_pol = this;
    }
    last_pol = this;
    int k;
    for (k=0;k<10;k++){
        storage[k] = 0;
    }
}
Polygon::~Polygon(){
    alive = false;
    if (prev){
        prev->next = next;
    }
    if (next){
        next->prev = prev;
    }
    if (this == last_pol){
        last_pol = prev;
    }
}
void Polygon::difPos(float dx,float dy,float na){
    int i;
    for (i=0;i<na;i++){
        xx[i] = xx[i]+dx;
        yy[i] = yy[i]+dy;
    }

}

void Polygon::resetPos(float *vx,float *vy,int na){

    free(xx);
    free(yy);
    n = na;
    xx = (float*)malloc(sizeof(float)*na);
    yy = (float*)malloc(sizeof(float)*na);
    int i;
    for (i=0;i<n;i++){
        xx[i] = vx[i];
        yy[i] = vy[i];
    }

}

void Polygon::moveY(int i,float add){
    if (i < n and i >= 0)
        yy[i] = yy[i]+add;
}
void Polygon::moveXAll(float add){
    int i;
    for (i=0;i<n;i++){
        xx[i] = xx[i]+add;
    }
}
void Polygon::moveYAll(float add){
    int i;
    for (i=0;i<n;i++){
        yy[i] = yy[i]+add;
    }
}
void Polygon::moveX(int i,float add){
    if (i < n and i >= 0)
        xx[i] = xx[i]+add;
}
void Polygon::setColor(uint8_t ra,uint8_t ga,uint8_t ba){
    r = ra;
    g  = ga;
    b = ba;
}
void Polygon::render(SDL_Surface* dst){
    if (enable)
        switch(t){
            case POLY_GENERIC:{
                Sint16* txx = (Sint16*)malloc(sizeof(Sint16)*n);
                Sint16* tyy = (Sint16*)malloc(sizeof(Sint16)*n);
                int i;
                for (i=0;i<n;i++){
                     txx[i] = floor(xx[i]);
                     tyy[i] = floor(yy[i]);
                }
                polygonRGBA(dst,(Sint16*)txx,(Sint16*)tyy,n,r,g,b,a);
                free(txx);
                free(tyy);
                break;}
            case POLY_GENERIC_FILL:{
                Sint16* txx = (Sint16*)malloc(sizeof(Sint16)*n);
                Sint16* tyy = (Sint16*)malloc(sizeof(Sint16)*n);
                int i;
                for (i=0;i<n;i++){
                     txx[i] = floor(xx[i]);
                     tyy[i] = floor(yy[i]);
                }
                filledPolygonRGBA(dst,(Sint16*)txx,(Sint16*)tyy,n,r,g,b,a);
                free(txx);
                free(tyy);
                break;}
            case POLY_PIXEL:{
                pixelRGBA (dst, (Sint16)xx[0], (Sint16)yy[0], r,  g,  b, a);
                break;
            case POLY_CIRCLE:{
                filledCircleRGBA (dst, (Sint16)xx[0], (Sint16)yy[0], (Sint16)storage[2], r,g,b,a);
                break;
            }
            }
        }
}

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

#include <stdlib.h>
#include "collision.h"

void Collision::setCollisionArea(int x,int y,int h,int w,int s){
        int stack = 0;
        for (int iy=y;iy<w;iy++)
            for (int ix=x;ix<h;ix++){
                while (cont[iy][ix][stack] != 0 and stack < 9){
                    stack++;
                }
                if (stack < 9)
                    cont[iy][ix][stack] = s;
            }
}

void Collision::setCollisionArea(int x,int y,int h,int w,int s,int stack){
        for (int iy=y;iy<w;iy++)
            for (int ix=x;ix<h;ix++){
                    cont[iy][ix][stack] = s;
            }
}

int Collision::hasBlock(int x,int y){
    if (x >= sizex || x <= 0){
        return 1;
    }
    if (y >= sizey || y <= 0){
        return 1;
    }
    int i,e;
    for (i=0;i<9;i++){
        e = cont[y][x][i];
        if (e != 0){
            return e;
        }
    }
    return 0;
}
int Collision::hasBlock(int x,int y,int stack){
    if (x >= sizex || x <= 0){
        return 1;
    }
    if (y >= sizey || y <= 0){
        return 1;
    }

    return cont[y][x][stack];
}
Collision::~Collision(){
   for (int iy = 0;iy<sizey;iy++){
        free(map[iy]);
   }
   free(map);
    for (int iy = 0;iy<sizey;iy++){
        for (int ix=0;ix<sizex;ix++){
            free(cont[iy][ix]);
        }
        free(cont[iy]);
    }
    free(cont);
   //Herdado de objeto, não precisa de free.
}
bool Collision::moveObjById(Objeto *o,int x,int y,bool c){
    Objeto *obj = o;
    if (obj != NULL){
        int xn = obj->getX(),yn = obj->getY();
        int h = obj->useclip ? obj->clips.h : obj->getImage()->h;
        int w = obj->useclip ? obj->clips.w : obj->getImage()->w;
        int stack = obj->stack;
        int sx,sy;
        int block = o->id;
        if (c)
        {
             for (sy=y;sy<y+h;sy++){
                for (sx=x;sx<x+w;sx++){
                    if (hasBlock(sx,sy,stack) != 0 && hasBlock(sx,sy,stack) != block){
                        return false;
                    }
                }
            }
        }


        for (sy=yn;sy<yn+h;sy++){
            for (sx=xn;sx<xn+w;sx++){
                cont[sy][sx][stack] = 0;
            }
        }

        for (sy=y;sy<y+h;sy++){
            for (sx=x;sx<x+w;sx++){
                cont[sy][sx][stack] = block;
            }
        }
        obj->setXY(x,y);

    }
    return true;
}
bool Collision::getCollisionState(float x,float y,int sprh,int sprw,float mapoffX,float mapoffY,int detect,int *f){
    (*f) = 0;
    for (int v=x;v<x+sprw;v++){ // Detectar em X
        for (int i=y;i<y+sprh;i++){ // Detectar em Y

                if( hasBlock(v-mapoffX,i-mapoffY) == detect ){
                    return true;
                }

        }
    }
    return false;
}

int Collision::adjustXy(float *x,float *y,float ox,float oy,int sprh,int sprw,float mapoffX,float mapoffY,int *dir,int id){
    int ret = 0;
    if ((*x-ox) > 0){
        for (int v=ox+sprw;v<(*x)+sprw;v++){ // Detectar de [x>X]
            for (int i=oy;i<oy+sprh;i++){ // Detectar lateral [
                if( hasBlock(v-mapoffX,i-mapoffY) != id and hasBlock(v-mapoffX,i-mapoffY) != 0 ){
                    *x = v-sprw;
                    *dir = 0;
                    ret = hasBlock(v-mapoffX,i-mapoffY);
                    break;
                }
            }
        }
    }else{
        for (int v=ox;v>*x;v--){ // Detectar de [x>X]
            for (int i=oy;i<oy+sprh;i++){ // Detectar lateral [
                if( hasBlock(v-mapoffX,i-mapoffY) != 0 and hasBlock(v-mapoffX,i-mapoffY) != id ){
                    *x = v+1;
                    *dir = 1;
                    ret = hasBlock(v-mapoffX,i-mapoffY);
                    break;
                }
            }
        }
    }
    if ((*y-oy) > 0){
        for (int v=oy+sprh;v<*y+sprh;v++){ // Detectar de [x>X]
            for (int i=ox;i<ox+sprw;i++){ // Detectar lateral [
                if( hasBlock(i-mapoffX,v-mapoffY) != 0 and hasBlock(i-mapoffX,v-mapoffY) != id){
                    *y = v-sprh;
                    *dir = 2;
                    ret = hasBlock(i-mapoffX,v-mapoffY);
                    break;
                }
            }
        }
    }else{
        for (int v=oy;v>*y;v--){ // Detectar de [x>X]
            for (int i=ox;i<ox+sprw;i++){ // Detectar lateral [
                if( hasBlock(i-mapoffX,v-mapoffY) != 0 and hasBlock(i-mapoffX,v-mapoffY) != id ){
                    *y = v+1;
                    *dir = 3;
                    ret = hasBlock(i-mapoffX,v-mapoffY);
                    break;
                }
            }
        }
    }
    return ret;
}


int Collision::adjustXy_(float *x,float *y,float ox,float oy,int sprh,int sprw,float mapoffX,float mapoffY,int *dir,int id){

    if ((*x-ox) > 0){
        for (int v=ox+sprw;v<(*x)+sprw;v++){ // Detectar de [x>X]
            for (int i=oy;i<oy+sprh;i++){ // Detectar lateral [
                if( hasBlock(v-mapoffX,i-mapoffY) != 0 and hasBlock(v-mapoffX,i-mapoffY) != id ){
                    *x = v-sprw;
                    *dir = 0;
                    return hasBlock(v-mapoffX,i-mapoffY);

                }
            }
        }
    }else{
        for (int v=ox;v>*x;v--){ // Detectar de [x>X]
            for (int i=oy;i<oy+sprh;i++){ // Detectar lateral [
                if( hasBlock(v-mapoffX,i-mapoffY) != 0 and hasBlock(v-mapoffX,i-mapoffY) != id ){
                    *x = v+1;
                    *dir = 1;
                    return hasBlock(v-mapoffX,i-mapoffY);
                }
            }
        }
    }
    if ((*y-oy) > 0){
        for (int v=oy+sprh;v<*y+sprh;v++){ // Detectar de [x>X]
            for (int i=ox;i<ox+sprw;i++){ // Detectar lateral [
                if( hasBlock(i-mapoffX,v-mapoffY) != 0 and  hasBlock(i-mapoffX,v-mapoffY) != id){
                    *y = v-sprh;
                    *dir = 2;
                    return hasBlock(i-mapoffX,v-mapoffY);
                }
            }
        }
    }else{
        for (int v=oy;v>*y;v--){ // Detectar de [x>X]
            for (int i=ox;i<ox+sprw;i++){ // Detectar lateral [
                if( hasBlock(i-mapoffX,v-mapoffY) != 0 and hasBlock(i-mapoffX,v-mapoffY) != id ){
                    *y = v+1;
                    *dir = 3;
                    return hasBlock(i-mapoffX,v-mapoffY);
                }
            }
        }
    }
    return 0;
}

bool Collision::collisionFind(float x,float y,float ox,float oy,int sprh,int sprw,float mapoffX,float mapoffY,int *type,int *dir){
    bool ret = false;
    if ((x-ox) > 0){
        for (int v=ox+sprw;v<(x)+sprw;v++){ // Detectar de [x>X]
            for (int i=oy;i<oy+sprh;i++){ // Detectar lateral [
                if( hasBlock(v-mapoffX,i-mapoffY) !=  0 ){
                    *type = hasBlock(v-mapoffX,i-mapoffY);
                    *dir = 0;
                    ret = true;
                    break;
                }
            }
        }
    }else{
        for (int v=ox;v>x;v--){ // Detectar de [x>X]
            for (int i=oy;i<oy+sprh;i++){ // Detectar lateral [
                if( hasBlock(v-mapoffX,i-mapoffY) != 0 ){
                    *type = hasBlock(v-mapoffX,i-mapoffY);
                    *dir = 1;
                    ret = true;
                    break;
                }
            }
        }
    }
    if ((y-oy) > 0){
        for (int v=oy+sprh;v<y+sprh;v++){ // Detectar de [x>X]
            for (int i=ox;i<ox+sprw;i++){ // Detectar lateral [
                if( hasBlock(i-mapoffX,v-mapoffY) != 0 ){
                    *type = hasBlock(v-mapoffX,i-mapoffY);
                    *dir = 2;
                    ret = true;
                    break;
                }
            }
        }
    }else{
        for (int v=oy;v>y;v--){ // Detectar de [x>X]
            for (int i=ox;i<ox+sprw;i++){ // Detectar lateral [
                if( hasBlock(i-mapoffX,v-mapoffY) != 0 ){
                    *type = hasBlock(v-mapoffX,i-mapoffY);
                    *dir = 3;
                    ret = true;
                    break;
                }
            }
        }
    }
    return ret;
}

Collision::Collision(int x,int y){
    sizex = x;
    sizey = y;

    cont = (int***)malloc(sizeof(int**)*y);
    for (int iy = 0;iy<y;iy++){
        cont[iy] = (int**)malloc(sizeof(int*)*x);
        for (int ix=0;ix<x;ix++){
            cont[iy][ix] = (int*)malloc(sizeof(int)*10);
            for(int kk=0;kk<9;kk++){
                cont[iy][ix][kk] = 0;
            }
        }

    }
    map = (int**)malloc(sizeof(int*)*y);
    for (int iy = 0;iy<y;iy++){
        map[iy] = (int*)malloc(sizeof(int)*x);
        for (int ix=0;ix<x;ix++)
            map[iy][ix] = 0;
    }
    Rcount = 0;


}
void Collision::clearId(int i)
{
    int x,y;
     for (y=0;y<sizey;y++){
        for (x=0;x<sizex;x++){
            if (map[y][x] == i){
               map[y][x] = (int)0;
            }
        }
    }
}


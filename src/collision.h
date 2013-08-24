#ifndef _COLLISION_
#define _COLLISION_

#define TYPE_BLOCK 1
#define TYPE_PRESS 2
#include <stdint.h>
#include "objects.h"


class Collision{
    int **map;
    int ***cont;
    Objeto **reserved;
    int sizex,sizey;
    public:
    int Rcount;
    Collision(int x,int y);
    ~Collision();
    void clearId(int);
    void setCollisionArea(int x,int y,int h,int w,int s);
    void setCollisionArea(int x,int y,int h,int w,int s,int stack);
    int hasBlock(int x,int y);
    int hasBlock(int x,int y,int stack);
    int adjustXy(float *x,float *y,float ox,float oy,int sprh,int sprw,float mapoffX,float mapoffY,int *dir,int id);
    bool getCollisionState(float x,float y,int sprh,int sprw,float mapoffX,float mapoffY,int detect,int *f);
    bool collisionFind(float x,float y,float ox,float oy,int sprh,int sprw,float mapoffX,float mapoffY,int *type,int *dir);
    int adjustXy_(float *x,float *y,float ox,float oy,int sprh,int sprw,float mapoffX,float mapoffY,int *dir,int id);

    Objeto *getObjById(int i){ return reserved[i];};
    void setObdjById(Objeto *o){ reserved[Rcount] = o; };
    bool moveObjById(Objeto *o,int x,int y,bool c);
};

#endif


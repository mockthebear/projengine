
#ifndef _POLYGONH_
#define _POLYGONH_
#include <SDL.h>
#include "definitions.h"
#include "base.h"
enum{
    POLY_GENERIC,
    POLY_GENERIC_FILL,
    POLY_PIXEL,
    POLY_CIRCLE,
};
class Polygon: public Base{
    int n;
    float *xx;
    float *yy;
    int t;

    uint8_t r,g,b,a;
    bool alive;

    public:
        bool enable;
        Polygon *next,*prev;
        Polygon(float *vx,float *vy,int na,int ta);
        ~Polygon();
        void resetPos(float *vx,float *vy,int na);
        void difPos(float dx,float dy,float na);
        void render(SDL_Surface*);
        void setColor(uint8_t,uint8_t,uint8_t);
        void setAlpha(uint8_t al){a = al;};
        bool isAlive(){return true;}
        void moveX(int i,float add);
        void moveY(int i,float add);
        void moveXAll(float add);
        void moveYAll(float add);

};

extern Polygon *mother_pol,*last_pol;

#endif


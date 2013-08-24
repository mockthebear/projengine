#include "polygon.h"
#include "base.h"
#include "math.h"
#include <stdlib.h>
#ifndef _PARTICLEH_
#define _PARTICLEH_

#define MAX_STORAGE 10

enum{
    SQUARE, //0
    TRIANGLE, //1
    PIXEL, //2
    DEBRIS, //3
    CIRCLE, //4
};
enum{
    NOTHING_EF,
    CIRCLE_EF, //1
    ELIPSE_EF, //2
    SPREAD_EF, //3
};
class Particle: public Base{

    Polygon **p;
    bool enabled;
    float storage[MAX_STORAGE];
    int n,step,amnt,shape;
    float *vx,*vy;

    void runCircle();
    void runElipse();
    void runSpread();

    public:
        int CTYPE,ef_type;
        float x,y,ox,oy;
        bool fade,blink,alive;
        int maxSteps;
        Particle(float,float,int,int);
        ~Particle();
        void enable();

        void disable();
        void doblink();
        void setColor(short r,short b,short g);
        void reset();
        void updatePosition(bool);
        bool isAlive() {return alive;};
        void perform();
        void setStorage(int i,float v);

};

#endif

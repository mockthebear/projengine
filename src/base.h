#include "imageloader.h"
#ifndef _BASEH_
#define _BASEH_

enum{
    OBJ,
    EFFECT_,
    MAP,
    POLYGON,
    PARTICLE,
    SOUND,
}; //This with ctype was too sexy!

class Base{
    float x, y;
    int type;
    SDL_Surface* image;
    public:
        Base *attach;
        int storage[10];
        int CTYPE;
        Base(){};
        SDL_Rect clips;
        bool useclip,alive;
        Base *next,*prev; //Effect list
        void setXY(float x1,float y1){x=x1;y=y1;};
        void setY(float y1){y=y1;};
        void setX(float x1){x=x1;};
        void setType(int t){type=t;};
        float getX(){return x;};
        float getY(){return y;};
        int getType(){return type;};
        SDL_Surface* getImage() {return image;};
        void setImage(char *nm) {image = IMgetImage(nm,&clips,&useclip);};
        void setImage(SDL_Surface *nm) {image = nm;};
};

void finish_him();
#endif // _BASEH_

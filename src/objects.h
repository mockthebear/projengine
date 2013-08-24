#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#ifndef _EFFECTS_
#define _EFFECTS_
#include "definitions.h"
#include "imageloader.h"
#include "base.h"

class Objeto: public Base {
    char *nome;
    SDL_Color color;
    bool invisible,transf_spr;
  public:

    int id,state[10],stack;
    bool onTop;
    float ofx,ofy,vY,vX,gX,gY,tX,tY;
    Objeto *next,*prev, *topSel;


    TTF_Font *font;
    //Construtores
    Objeto(char *adrs,float,float);
    Objeto();
    //Destrutor
    ~Objeto();
    //Gets
    char *getText(){ return nome;};

    bool getInvisble(){return invisible;};

    //Set

    void setFont(char*,int);
    void setText(char*);
    void setVisible(bool vis){invisible = vis;};
    void setTextColor(int,int,int);
    void flip(double angle,double size,double smooth);
    void setClips(int X,int Y,int H,int W);
    //Etc~
    bool render(SDL_Surface*);
};
extern Objeto *mother;
extern Objeto *last;
Objeto *createObject(char *adrs,float,float);
#endif

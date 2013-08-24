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

#include "objects.h"
#include "logs.h"
#include "collision.h"
#include <string.h>
#include <math.h>
#include "SDL_rotozoom.h"
#include "console.h"
Objeto *mother = NULL;
Objeto *last = NULL;
extern Log *output;

Objeto *createObject(char *adrs,float xx,float yy){
    Objeto *obj = new Objeto(adrs,xx,yy);
    if (last != NULL){
      last->next = obj;
      obj->prev = last;
   }else{
      mother = obj;
   }
   last = obj;
   return obj;
}

Objeto::~Objeto(){

    if (mother == this){
        //N pode apagar mother
    }else{


        alive = false;
        if (prev){
            prev->next = next;
        }

        if (next){
            next->prev = prev;
        }

        if (this == last){
            last = prev;
        }

        topSel = NULL;

        //free (nome);
        if (font){
             TTF_CloseFont(font);
        }
        if (transf_spr){
            SDL_FreeSurface(getImage());
        }
    }
}
void Objeto::flip(double angle,double size,double smooth){
    SDL_Surface* old = getImage();
    setImage(rotozoomSurface(old, angle,  size,0));
    if(transf_spr)
        SDL_FreeSurface(old);
    transf_spr = true;

}

void Objeto::setFont(char *nm,int sz){
    char FNTT[80];
    sprintf(FNTT,"%s",nm);
    font = TTF_OpenFont( FNTT, sz );
    strcpy(FNTT,nome);
    setText(FNTT);

}
void Objeto::setTextColor(int r,int b,int g){
    char FNTT[80];
    color.r =r;
    color.b = b;
    color.g = g;
    strcpy(FNTT,nome);
    setText(FNTT);
}
void Objeto::setText(char *adrs){
    int n=0;
    free(nome);
    for (n=0;adrs[n] != '\0';n++);
    nome = (char*)malloc(sizeof(char)*(n+1));
    for (n=0;adrs[n]!= '\0';n++){
        nome[n] = adrs[n];
    }
    nome[n] = '\0';
    if (getImage())
        SDL_FreeSurface(getImage());
    setImage(TTF_RenderText_Blended( font, nome, color ));
}


Objeto::Objeto(){
    prev = next = NULL;
    return;
}
int bjid = 0;
Objeto::Objeto(char adrs[255],float x_,float y_) {
    if (adrs == NULL){
        prev = next = NULL;
        return;
    }
    id = bjid;
    bjid++;
    CTYPE = OBJ;
    transf_spr = false;
    stack = 0;
    int n=0;
    bool s = false;
    if (x_ == -1){
        x_ = y_ = 1;
        s = true;
    }
    n = strlen(adrs);
    nome = (char*)malloc(sizeof(char)*(n+3));
    strcpy(nome,adrs);
    attach = NULL;
    font = NULL;
    invisible = true;
    vX = vY = ofx = ofy = gY = gX = tX = tY =0;
    useclip = false;
    setImage(IMgetImage(nome,&clips,&useclip));
    setType(STATIC_OBJ);
    onTop  = false;
    topSel = next = prev = NULL;
    if (getImage() == NULL)
    {
        font = TTF_OpenFont((char*)"data/defaut.ttf", 11 );
        color.r = 255;
        color.g = 0;
        color.b = 0;
        setImage(TTF_RenderText_Blended( font, nome, color ));
        transf_spr = true;
        if (getImage() == NULL){
            exit(5);
        }
        //onTop = true;
        setType(TEXT_OBJ);
    }
    alive = true;
    setXY(x_,y_);
    if (s){
        if (last != NULL){
            last->next = this;
            prev = last;
        }else{
            mother = this;
        }
        last = this;
   }
}
void Objeto::setClips(int X,int Y,int H,int W){
    useclip = true;
    clips.x = X;
    clips.y = Y;
    clips.h = H;
    clips.w = W;
}

bool Objeto::render(SDL_Surface* display){
    if (this == mother || invisible == false){
        return false;
    }
    SDL_Rect dest;
    dest.x = static_cast<int>(getX()+ofx);
    dest.y = static_cast<int>(getY()+ofy);
    if (!useclip){
        return (SDL_BlitSurface(getImage(), NULL, display, &dest) != 0);
    }else{
        return (SDL_BlitSurface(getImage(), &clips, display, &dest) != 0);
    }
}

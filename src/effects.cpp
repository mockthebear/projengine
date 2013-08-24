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

#include "effects.h"
#include <SDL/SDL_image.h>
#include "SDL_rotozoom.h"
#include "imageloader.h"

Effect *mother_ef = NULL;
Effect *last_ef = NULL;

Effect::Effect(char *nome,int x_,int y_,int frames,int lines,int sizex,int sizey,int speed,bool loop_param,int tt):Base(){
    loop = loop_param;
    setXY(x_,y_);
    frameskip = 1;
    CTYPE = EFFECT_;
    x_off = y_off = initframe  =  frame =0;
    setType(tt);
    attach = NULL;
    prev = next = NULL;
    timer_.start();
    nextFrame_t = timer_.get_ticks() + speed;
    alive = true;
    transf_spr = false;
    velocity = speed;
    clips = (SDL_Rect*)malloc(sizeof(SDL_Rect)*frames*lines);
    maxframes = frames*lines;
    setImage(nome);
    int n = -1;
    for (int l=0;l<lines;l++){
        for (int i=0;i<frames;i++){
            n++;
            clips[ n ].x = sizex * i;
            clips[ n ].y = sizey * l;
            clips[ n ].w = sizex;
            clips[ n ].h = sizey ;
        }
    }
    if (last_ef != NULL){
        last_ef->next = this;
        prev = last_ef;
    }else{
        mother_ef = this;
    }
    status = true;
    last_ef = this;
}
void Effect::flip(double angle,double size,double smooth){
    SDL_Surface* old = getImage();
    setImage(rotozoomSurface(old, angle,  size,0));
    if(transf_spr)
        SDL_FreeSurface(old);
    transf_spr = true;

}
Effect::~Effect(){
        alive = false;
        if (prev){
            prev->next = (Effect*)next;
        }
        if (next){
            next->prev = (Effect*)prev;
        }
        if (this == last_ef){
            last_ef = (Effect*)prev;
        }
        if (transf_spr)
            SDL_FreeSurface(getImage());
        free(clips);
}

bool Effect::canchangeFrame(){
    return (timer_.get_ticks() >= nextFrame_t);
}
void Effect::show(SDL_Surface *display){

    if (frame <= maxframes && frame >= 0){
        SDL_Rect dest;

        if (attach){
            dest.x = static_cast<int>(attach->getX()+x_off);
            dest.y = static_cast<int>(attach->getY()+y_off);
        }else{
            dest.x = static_cast<int>(getX()+x_off);
            dest.y = static_cast<int>(getY()+y_off);
        }
        SDL_BlitSurface( getImage(), &clips[frame], display, &dest );
    }
}
void Effect::skipFrane() {
    if (status){
        if (frameskip == 1){
            frame = frame >= maxframes-1 ? initframe :  frame+1;
        }else{
            frame = frame <= 0 ? maxframes-1 : frame-1;
        }

    }
    nextFrame_t = timer_.get_ticks() + velocity;
    //frame = ((status == true) ? () : (frame)); };
}

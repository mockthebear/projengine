#ifndef EFFECTS_H


#define EFFECTS_H
#include "definitions.h"
#include <SDL/SDL.h>
#include "timer.h"
#include "objects.h"
#include "base.h"

class Effect: public Base {
    int maxframes,nextFrame_t,frame,initframe;
    bool loop,status,transf_spr;

  public:
    int x_off,y_off,frameskip; // X/Y offset
    Timer timer_;   //Timer to configure effect speed
    int velocity;   //speed
    SDL_Rect *clips;    //vector to frames

    int getInitFrame() {return initframe;};
    void setInitFrame(int i){initframe = i;};
    void setPause(bool p) {status = p;};
    void setLoop(bool s) {loop = s;};
    bool isLooping() {return loop;};
    void setAlive(bool s) {alive = s;};
    int getFrame() {return frame;};
    bool canchangeFrame();
    void flip(double angle,double size,double smooth);
    int getMaxFrames() {return maxframes;};
    void skipFrane();// {frame = ((status == true) ? (frame >= maxframes-1 ? initframe :  frame+1) : (frame)); nextFrame_t = timer_.get_ticks() + velocity;};
    void show(SDL_Surface*);
    Effect(char*,int,int,int,int,int,int,int,bool,int);
    ~Effect();
};

extern Effect *mother_ef;
extern Effect *last_ef;
#endif // EFCTS

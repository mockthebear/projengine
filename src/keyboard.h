#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "objects.h"
#include "effects.h"
#include "maploader.h"
#include "definitions.h"

#include "console.h"
#include "luascript.h"
#include "particles.h"
extern luaScript *Lua;

extern Console *consolemain;

class User{
    bool PRESS[1024];
    public:
    int MOUSE_X,MOUSE_Y;
    User();
    int parseEvents(SDL_Event *ev);
    void mouseDown(SDL_Event *ev);
    void mouseUp(SDL_Event *ev);
    void mouseMotion(int,int);

    int keyPressed(int key);
    void keyRelease(SDL_Event *ev,int key);
    void whileKeyPressed(SDL_Event *ev);
};

extern float N;
extern Particle *part;
//extern bool PRESS[255]; //Usado posteriormente no controle do teclado

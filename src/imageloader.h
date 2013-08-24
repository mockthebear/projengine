#include <SDL/SDL.h>  //SDL, lib grafica usada
#include <SDL/SDL_image.h> //Usado para carregar facilmente imagens

#define MAX_IMAGES_LOAD 40
#ifndef _IMGLDR_
#define _IMGLDR_

extern char img_list[][80];
extern int Nimgs;

extern SDL_Surface* IMgetImage(char *nome,SDL_Rect *clips,bool *useclip);
extern SDL_Surface **surfaceList;
SDL_Surface* IMG_Load_ENGINE(char *);
#endif // _IMGLDR_

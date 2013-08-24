
#ifndef _MAP_
#define _MAP_
#include "objects.h"
#include "effects.h"
#include "collision.h"


class Map: public Objeto {
    int obj_count;
    Collision *collision_map;
    unsigned char *mapBin;
    int mapSize_bin,sx,sy;
  public:
    Objeto **map_objs;
    Collision *getMap(){return collision_map;};
    Map(char *adrs,char *mapdir);
    ~Map();

    int getObjCount() {return obj_count;};
  };
  extern int SCREEN_Width,SCREEN_Height;
#endif

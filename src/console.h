
#ifndef _CONSOLEH_
#define _CONSOLEH_
#include "objects.h"
typedef struct CHR{
    Objeto *obj;
    struct CHR *next;
}Line;
class Console{
    public:
    int x,y;
    bool enabled;
    int maxL;
    Line *lines,*mdr;
    char wrt[15][255];
    Console(int,int,int);
    void addLine(char*);

    void clear();
    void print(char*);


};
extern Console *consolemain;
#endif

#include "definitions.h"
#include <stdlib.h>
#include <stdio.h>

#ifndef _LOGSH_
#define _LOGSH_

class Log{
    FILE *file;
    int pos, size;
    public:
    Log(char *name);
    ~Log();

    int getSize(){return size;};
    int getPos(){return pos;};
    void write(char *str);
    void write(const char *str);
    void fwrite(char *str);


};

#endif

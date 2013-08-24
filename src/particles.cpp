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

#include "particles.h"
Particle *mother_part;
Particle *last_part;
float *generateParticleX(int type,int *s){
    float* vx = NULL;
    switch(type){
        case CIRCLE:{
            vx = (float*)malloc(sizeof(float)*2);
            vx[0] = 0;
            vx[1] = 3;
            *s = 2;
            break;
        }
        case PIXEL:{
            vx = (float*)malloc(sizeof(float));
            vx[0] = 0;
            *s = 1;
            break;
            }
        case SQUARE:{
            int size_ = 4;
            *s = size_;
            vx = (float*)malloc(sizeof(float)*size_);
            vx[0] = 0;
            vx[1] = 3;
            vx[2] = 3;
            vx[3] = 0;
            break;
        }case TRIANGLE:{
            int size_ = 3;
            *s = size_;
            vx = (float*)malloc(sizeof(float)*size_);
            vx[0] = 0;
            vx[1] = 3;
            vx[2] = 1.5;
            break;
        }case DEBRIS:{
            int size_ = 10;
            *s = size_;
            vx = (float*)malloc(sizeof(float)*size_);
            vx[0] = 0;
            vx[1] = 1;
            vx[2] = 3;
            vx[3] = 4;
            vx[4] = 5;
            vx[5] = 4;
            vx[6] = 4.5;
            vx[7] = 3;
            vx[8] = 2.5;
            vx[9] = 1;

            break;
        }


    }
    return vx;
}
float *generateParticleY(int type,int *s){
    float* vy = NULL;
    switch(type){
        case CIRCLE:{
            *s = 2;
            vy = (float*)malloc(sizeof(float)*2);
            vy[0] = 0;
            vy[1] = 3;
            break;
        }
        case PIXEL:{
            *s = 1;
            vy = (float*)malloc(sizeof(float));
            vy[0] = 0;
            break;
        }
        case SQUARE:{
            int size_ = 4;
            *s = size_;
            vy = (float*)malloc(sizeof(float)*size_);
            vy[0] = 0;
            vy[1] = 0;
            vy[2] = 3;
            vy[3] = 3;

            break;
        }case TRIANGLE:{
            int size_ = 3;
            *s = size_;
            vy = (float*)malloc(sizeof(float)*size_);
            vy[0] = 0;
            vy[1] = 0;
            vy[2] = 3;
            break;
        }case DEBRIS:{
            int size_ = 10;
            *s = size_;
            vy = (float*)malloc(sizeof(float)*size_);
            vy[0] = 0;
            vy[1] = 0.5;
            vy[2] = 1.5;
            vy[3] = 0.5;
            vy[4] = 0;
            vy[5] = -0.5;
            vy[6] = -1.5;
            vy[7] = -0.5;
            vy[8] = -1.5;
            vy[9] = -0.5;
            break;
        }

    }
    return vy;
}

Particle::Particle(float xx,float yy,int a,int shapee){
    n = a;
    CTYPE = PARTICLE;
    x = ox = xx;
    y = oy = yy;
    step = 0;
    ef_type = NOTHING_EF;
    enabled = false;
    maxSteps = -1;
    shape = shapee;

    p = (Polygon**)malloc(sizeof(Polygon*)*n);
    vx = generateParticleX(shapee, &amnt);
    vy = generateParticleY(shapee, &amnt);
    int i;
    for (i=0;i<MAX_STORAGE;i++){
        storage[i] = 0;
    }
    alive = true;
    fade = false;
    blink = false;
    next = prev = NULL;
    int oldx = vx[1];
    for (i=0;i<amnt;i++){
        vx[i] = vx[i]+x;
        vy[i] = vy[i]+y;
    }
    for (i=0;i<n;i++){

        if (shapee != PIXEL and shapee != CIRCLE)
        {
            p[i] = new Polygon(vx,vy,amnt,POLY_GENERIC_FILL);
        }else{
            p[i] = new Polygon(vx,vy,amnt,POLY_CIRCLE);

        }

        if (shape == CIRCLE)
            storage[2] = p[i]->storage[2] = oldx;
        p[i]->enable = false;

    }

   if (last_part != NULL){
        last_part->next = this;
        prev = last_part;
    }else{
        mother_part = this;
    }
    last_part = this;

}

Particle::~Particle(){
    free(p);
    int i;
    for (i=0;i<n;i++){
        delete p[i];
    }
    alive = false;
    if (prev){
        prev->next = next;
    }
    if (next){
        next->prev = prev;
    }
    if (this == last_part){
        last_part = (Particle*)prev;
    }
    free(vx);
    free(vy);
}
void Particle::setStorage(int i,float v){
    storage[i] = v;
}
void Particle::updatePosition(bool rs){
    if (rs){
        free(vx);
        free(vy);
        vx = generateParticleX(shape, &amnt);
        vy = generateParticleY(shape, &amnt);
        int i;
        for (i=0;i<amnt;i++){
            vx[i] = vx[i]+x;
            vy[i] = vy[i]+y;
        }
        for (i=0;i<n;i++){
            p[i]->resetPos(vx,vy,amnt);
        }
    }else{
        float xdif = (x-ox);
        float ydif = (y-oy);
        oy = y;
        ox = x;
        int i;
        for (i=0;i<n;i++){
            p[i]->difPos(xdif,ydif,amnt);
        }

    }
}
void Particle::reset(){
    int i;
    for (i=0;i<n;i++){
        p[i]->resetPos(vx,vy,amnt);
        int k;
        for (k=0;k<10;k++){
            p[i]->storage[k] = 0;
        }
        if (shape == CIRCLE)
            p[i]->storage[2] = storage[2];
    }
    step = 0;
}
void Particle::enable(){
    int i;
    enabled = true;
    for (i=0;i<n;i++){
        p[i]->enable = true;
    }
}
void Particle::disable(){
    int i;
    for (i=0;i<n;i++){
        p[i]->enable = false;
    }
    enabled = false;
}
void Particle::doblink(){
   int i;
   for (i=0;i<n;i++){
        if (blink)
            p[i]->setColor(rand()%255,rand()%255,rand()%255);
   }
}
void Particle::setColor(short r,short b,short g){
   int i;
   for (i=0;i<n;i++){
        p[i]->setColor(r,g,b);
   }
}
void Particle::perform(){
    switch (ef_type){
        case CIRCLE_EF:{
            runCircle();
            break;
        }case ELIPSE_EF:{
            runElipse();
            break;
        }case SPREAD_EF:{
            runSpread();
            break;
        }
    }
}

void Particle::runSpread(){
   if (enabled){
       step++;
       int i;
       for (i=0;i<n;i++){
            if (p[i]->storage[0] == 0){
                p[i]->storage[0] = (rand()%3600);
            }
            if (p[i]->storage[1] == 0){
                p[i]->moveXAll(sin((3.1415/180.0)* (p[i]->storage[0]/1.0)  ));
                p[i]->moveYAll(cos((3.1415/180.0)* (p[i]->storage[0]/1.0) ));
                p[i]->storage[1] = rand()%((int)storage[0] == 0 ? 1 : (int)storage[0] );
            }else{
                p[i]->storage[1]--;
            }
            if (blink){
                p[i]->setColor(rand()%255,rand()%255,rand()%255);
            }
            if (fade){
                if (maxSteps == -1 || maxSteps == 0){
                    p[i]->setAlpha(rand()%255);
                }else{
                    p[i]->setAlpha( 255.0 - (((float)step/(float)maxSteps))*255.0 );
                }
            }
        }
        if (maxSteps != -1 and maxSteps == step){
            reset();
            disable();
        }
   }
}

void Particle::runCircle(){
   if (enabled){
       step++;
       int i;
       for (i=0;i<n;i++){
            //int cx = 0,cy = 0;
            p[i]->moveXAll( sin((3.1415/180.0)*( (360.01/(float)n) * ((float)i) ))  );
            p[i]->moveYAll( cos((3.1415/180.0)*( (360.01/(float)n) * ((float)i) ))  );
            if (blink){
                p[i]->setColor(rand()%255,rand()%255,rand()%255);
            }
            if (fade){
                if (maxSteps == -1 || maxSteps == 0){
                    p[i]->setAlpha(rand()%255);
                }else{
                    p[i]->setAlpha( 255.0 - (((float)step/(float)maxSteps))*255.0 );
                }
            }
        }
        if (maxSteps != -1 and maxSteps == step){
            reset();
            disable();
        }
   }
}
void Particle::runElipse(){
   if (enabled){
       step++;
       int i;
       for (i=0;i<n;i++){
            int cx = 0,cy = 0;
            p[i]->moveXAll( cx +   storage[0]*sin((3.1415/180.0)*( (360.01/(float)n) * ((float)i) ))  );
            p[i]->moveYAll( cy +   storage[1]*cos((3.1415/180.0)*( (360.01/(float)n) * ((float)i) ))  );
            if (blink){
                p[i]->setColor(rand()%255,rand()%255,rand()%255);
            }
            if (fade){
                if (maxSteps == -1 || maxSteps == 0){
                    p[i]->setAlpha(rand()%255);
                }else{
                    p[i]->setAlpha( 255.0 - (((float)step/(float)maxSteps))*255.0 );
                }
            }
        }
        if (maxSteps != -1 and maxSteps == step){
            reset();
            disable();
        }
   }
}

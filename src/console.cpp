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
#include "console.h"

#define LINE_DISTANCE 15


Console::Console(int x,int y,int max){
    this->x = x;
    enabled = false;
    this->y = y;
    maxL = max;
    mdr = lines = (Line*)malloc(sizeof(Line));
    lines->obj = (createObject((char*)" ",x,y));
    lines->obj->setTextColor(0,0,0);
    lines->obj->setFont((char*)"data/vgafix.fon",12);
    lines->next = NULL;
    int i=10;
    for (i=0;i<maxL;i++){
        addLine((char*)" ");
    }
}
void Console::clear(){

    Line *le = lines;
    while (le != NULL){
        //olda = le;
        le = le->next;
    }
}

void Console::print(char *str){
    if (enabled)
        addLine(str);
}

void Console::addLine(char* str){
    int i=1,e=0;
    Line *l = lines;
    Line *old = NULL;
    while (l != NULL){
        old = l;
        e++;
        i = i+LINE_DISTANCE;
        l = l->next;
    }

    if (e > maxL){
        Line *bgn = mdr->next,*back_;
        back_ = bgn->next;
        delete bgn->obj;
        free(bgn);
        mdr->next = bgn = back_;
        while (bgn != NULL){
            bgn->obj->setY(bgn->obj->getY()-LINE_DISTANCE);
            bgn = bgn->next;
        }
    }
    old->next = (Line*)malloc(sizeof(Line));
    l = old->next;
    char juj[255];
    sprintf(juj,"%s",str);
    old->next->obj =(createObject((char*)juj,x,y+i));
    old->next->obj->setTextColor(0,0,0);
    old->next->obj->onTop = true;
    old->next->obj->setText(juj);
    old->next->obj->setFont((char*)"data/vgafix.fon",12);
    old->next->next = NULL;

}

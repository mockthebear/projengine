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

#include "logs.h"

#include <cstdio>
#define _DEBUG_

Log::Log(char *nome){
    file = fopen(nome,"wb");
    fseek(file, 0L, SEEK_END);
    size = ftell(file);
    pos = 0;
    fseek(file, 0L, SEEK_SET);
    fprintf(file,"Logs started\n");
}

Log::~Log(){
    fprintf(file,"\nLogs closed!\n");
    fclose(file);
}

void Log::write(const char *str){
    #ifdef _DEBUG_
    fprintf(file,"%s",str);
    #endif
}

void Log::write(char *str){
    #ifdef _DEBUG_
    fprintf(file,"%s",str);
    #endif
}

void Log::fwrite(char *str){
    fprintf(file,"%s",str);
}

#include <stdio.h>
#include <stdlib.h>
#include "minish.h"

int builtin_exit (int argc, char ** argv){

    int status;                         // admite un parámetro que es el status de retorno
    
    if (argc == 1){                     // si hay un argumento solo 
        status = globalstatret;         // status es el del ultimo comando     
    } else {
        status = atoi(argv[1]);         // sino preguntar
    }
    
    write_history_file();               // actualiza history
    exit(status);                       // termina el shell

    return status;
}
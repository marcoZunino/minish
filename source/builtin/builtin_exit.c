#include <stdio.h>
#include <stdlib.h>
#include "minish.h"

int builtin_exit (int argc, char ** argv){

    int status;                         // admite un parámetro que es el status de retorno
    
    if (argc == 1){                     // si hay un argumento solo 
        status = globalstatret;         // status es el del ultimo comando     
    } else if (argc == 2) {
        status = atoi(argv[1]);         // se castea el parametro a entero
        //CHEQUEAR QUE SEA CORRECTO EL PARAMETRO (NUMERO ENTRE 0 Y 255)
    } else {
        //error de argumentos
        return 1;
    }
    
    write_history_file();               // actualiza history
    exit(status);                       // termina el shell

    return status;
}
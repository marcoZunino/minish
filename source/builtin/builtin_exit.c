#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <error.h>
#include "minish.h"

int builtin_exit (int argc, char ** argv){

    int status;                         // admite un parámetro que es el status de retorno
    
    if (argc == 1){                     // si hay un argumento solo 
        status = globalstatret;         // status es el del ultimo comando     
    } else if (argc == 2) {

        for (int p=0; argv[1][p] != '\0'; p++) { //se chequea que no sean letras
            if ((argv[1][p] < '0' || argv[1][p] > '9') && argv[1][p] != '-') {
                error(0, errno, "error exit: invalid argument %s", argv[1]);
                return 1;
            }
        }

        status = atoi(argv[1]);         // se castea el parametro a entero
        
        if (status < 0 || status > 255){
            error(0, errno, "error exit: invalid argument %s, must be between 0 and 255", argv[1]);
            return 1;
        }

    } else {
        error(0, errno, "error exit: too many arguments");  //error de argumentos
        return 1;
    }
    
    write_history_file(history_length);      // actualiza el archivo de history
    exit(status);                            // termina el shell

    return status;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "minish.h"

int ejecutar(int argc, char **argv) {
    int status = 0; // = valor por defecto
    // fprintf(stderr, "Will execute command %s\n", argv[0]);

    struct builtin_struct * b = builtin_lookup(argv[0]);    //se busca el comando
    if (b != NULL) {    //es comando interno
        status = b->func(argc, argv); //se invoca a la funcion del comando interno
    } else {
        status = externo(argc, argv); //no es interno, se intenta ejecutar como externo
    }

    return status;
}
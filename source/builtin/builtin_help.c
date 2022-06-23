#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <error.h>
#include "minish.h"

int builtin_help (int argc, char ** argv) {

    if (argc == 1) {                        // Sin argumentos escribe un texto de ayuda 
        printf("%s\n", HELP_HELP);          // indicando qué comandos internos existen
    } else if (argc == 2) {                                
        struct builtin_struct * b = builtin_lookup(argv[1]);    
        if (b != NULL) {                                        // si b no es null significa que es un builtin
            printf("%s\n", b->help_txt);                        // se muestra la ayuda de ese comando
        } else {
            error(0, errno, "error help %s: not found", argv[1]); //no existe el comando interno
            return 1;
        }
    } else {
        error(0, errno, "error gid: too many arguments");
        return 1;
    }

    return 0;
}
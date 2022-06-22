#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minish.h"

int builtin_help (int argc, char ** argv) {
    int status = 0;

    if (argc == 1) {                        // Sin argumentos escribe un texto de ayuda 
        printf("%s\n", HELP_HELP);          // indicando qué comandos internos existen
    } else {                                
        struct builtin_struct * b = builtin_lookup(argv[1]);    
        if (b != NULL) {                                        // si b no es null significa que es un builtin
            printf("%s\n", b->help_txt);                        // se muestra la ayuda de ese comando
        } else {
            printf("No se encontró comando %s\n", argv[1]);
            status = 1;
        }
    }

    return status;
}
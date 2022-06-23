#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <error.h>
#include "minish.h"
#define DEFAULT_COMMANDS 10

int builtin_history (int argc, char ** argv) {

    int n = DEFAULT_COMMANDS;           //cantidad por defecto de comandos mostrados
    if (argc == 1) {
    } else if (argc == 2) {

        for (int p=0; argv[1][p] != '\0'; p++) { //se chequea que no sean letras
            if (argv[1][p] < '0' || argv[1][p] > '9') {
                error(0, errno, "error history: invalid argument %s", argv[1]);
                return 1;
            }
        }

        n = atoi(argv[1]);              //se castea a entero el argumento
        
    } else {
        error(0, errno, "error history: too many arguments");   //error de argumentos
        return 1;
    }

    struct history_entry * entry = history_arr->last;   //puntero al ultimo comando
    if (entry == NULL) {
        error(0, errno, "error history");
        return 1;
    }
    for (int c = 0; c < n && entry->prev != NULL; entry = entry->prev, c++) {
    //se recorre la lista del history hacia atras
        printf("%i: %s", c, entry->command);            //se imprimen los ultimos 'n' comandos
    }

    return 0;
}
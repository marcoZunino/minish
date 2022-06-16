#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "minish.h"

int ejecutar(int argc, char **argv) {
    int status = 0; // = valor por defecto
    // fprintf(stderr, "Will execute command %s\n", argv[0]);

    struct builtin_struct * b = builtin_lookup(argv[0]);
    if (b != NULL) {
        status = b->func(argc, argv);
    } else {
        status = externo(argc, argv);
    }

    return status;
}
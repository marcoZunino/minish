#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <error.h>
#include "minish.h"

int builtin_getenv (int argc, char ** argv) {

    if (argc > 1) {
        int status = 0;
        for (int i = 1; i < argc; i++) {
            char * value = getenv(argv[i]);             // obtiene una variable de ambiente
            if (value != NULL) {                        // devuelve un puntero al correspondiente value o NULL si no hay coincidencia
                printf("%s = %s\n", argv[i], value);
            } else {
                error(0, errno, "error getenv %s", argv[i]);    //no existe la variable
                status = 1;
            }
        }
        return status;
    } else {
        error(0, errno, "error getenv: too few arguments");
        return 1;
    }

}
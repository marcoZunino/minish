#include <stdio.h>
#include <stdlib.h>
#include "minish.h"

int builtin_getenv (int argc, char ** argv) {
    //environ
    if (argv[1] == NULL) printf("lista\n"); //imprimir toda la lista;
    else {
        for (int i = 1; i < argc; i++) {
            char * value = getenv(argv[i]);
            if (value != NULL) printf("%s = %s\n", argv[i], getenv(argv[i]));
            else printf("getenv %s error\n", argv[i]);
        }
    }

    return 0;
}
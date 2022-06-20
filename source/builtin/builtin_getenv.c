#include <stdio.h>
#include <stdlib.h>
#include "minish.h"

int builtin_getenv (int argc, char ** argv) {
    //environ
    if (argc == 2) {
        for (int i = 1; i < argc; i++) {
            char * value = getenv(argv[i]);
            if (value != NULL) {
                printf("%s = %s\n", argv[i], value);
            } else {
                printf("getenv %s error\n", argv[i]);
                return -1;
            }
        }
    } else {
        //error en argumentos
        return -1;
    }

    return 0;
}
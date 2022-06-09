#include <stdio.h>
#include <stdlib.h>
#include "minish.h"

int builtin_getenv (int argc, char ** argv) {
    //environ
    int status = 0;
    if (argv[1] != NULL) {
        for (int i = 1; i < argc; i++) {
            char * value = getenv(argv[i]);
            if (value != NULL) {
                printf("%s = %s\n", argv[i], getenv(argv[i]));
            } else {
                printf("getenv %s error\n", argv[i]);
                status = 1;
            }
        }
    } else status = 1;

    return status;
}
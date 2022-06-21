#include <stdio.h>
#include <stdlib.h>
#include "minish.h"

int builtin_getenv (int argc, char ** argv) {

    if (argc > 1) {
        int status = 0;
        for (int i = 1; i < argc; i++) {
            char * value = getenv(argv[i]);
            if (value != NULL) {
                printf("%s = %s\n", argv[i], value);
            } else {
                printf("getenv %s error\n", argv[i]);
                status = 1;
            }
        }
        return status;
    } else {
        //error en argumentos
        return 1;
    }

}
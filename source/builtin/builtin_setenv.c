#include <stdio.h>
#include <stdlib.h>
#include "minish.h"

int builtin_setenv (int argc, char ** argv) {
    int status = 0;

    if (argc != 3) {
        printf("setenv exactamente solo dos argumentos: variable y valor\n");
        status = 1;
    } else { 
        setenv(argv[1], argv[2], 1);
    }
    
    return status;
}
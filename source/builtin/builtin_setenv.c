#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <error.h>
#include "minish.h"

int builtin_setenv (int argc, char ** argv) {

    if (argc != 3) {                            // setenv debe admitir solo 2 argumentos: variable y valor
        error(0, errno, "error setenv: argmuents must be 2");
        return 1;
    } else {
        setenv(argv[1], argv[2], 1);            // cambia o agrega una variable de ambiente
    }
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <error.h>
#include "minish.h"

int builtin_unsetenv (int argc, char ** argv) {
    
    if (argc == 1) {
        error(0, errno, "error unsetenv: too few arguments");
        return 1;
    }
    for (int i = 1; i < argc; i++) {
            if (getenv(argv[i]) != NULL) {          // buscamos las variables de ambiente
                if (unsetenv(argv[i]) != 0) {       // elimina las variables de ambiente y chequea errores
                    error(0, errno, "error unsetenv");
                    return 1;
                }
                printf("%s unset \n", argv[i]);
            }
            else {
                error(0, errno, "error unsetenv: %s not found", argv[i]);
                return 1;
            }
        }
    return 0;
}
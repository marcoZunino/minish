#include <stdio.h>
#include <stdlib.h>
#include "minish.h"

int builtin_unsetenv (int argc, char ** argv) {
    int status = 0;
    
    for (int i = 1; i < argc; i++) {
            if (getenv(argv[i]) != NULL) {
                status = unsetenv(argv[i]);
                printf("%s unset \n", argv[i]);
            }
            else {
                printf("unsetenv %s error\n", argv[i]);
                status = 1;
            }
        }
    return status;
}
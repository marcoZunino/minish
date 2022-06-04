#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minish.h"

int  builtin_help (int argc, char ** argv){
    int status = 0;
    
    struct builtin_struct b;
    if (argv[1] == NULL) argv[1] = "help";
    for (int i=0; (b = builtin_arr[i]).cmd != NULL; i++) {
        if (strcmp(argv[1], b.cmd) == 0) {
            printf("%s\n", b.help_txt);
            break;
        }
    }
    if (b.cmd == NULL) printf("help externo\n");

    return status;
}
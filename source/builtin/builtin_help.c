#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minish.h"

int builtin_help (int argc, char ** argv) {
    int status = 0;

    if (argv[1] == NULL) printf("%s\n", HELP_HELP);
    else {

        struct builtin_struct * b = builtin_lookup(argv[1]);
        if (b != NULL) printf("%s\n", b->help_txt);
        else printf("No se encontró comando %s\n", argv[1]);
    }

    return status;
}
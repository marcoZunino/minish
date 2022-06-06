#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "minish.h"

int builtin_cd (int argc, char ** argv) {

    int status = 0;
    if (argv[1] == NULL) status = chdir(getenv("HOME"));
    else if (strcmp(argv[1],"-") == 0)
    return 0;
}
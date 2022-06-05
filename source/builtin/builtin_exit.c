#include <stdio.h>
#include <stdlib.h>
#include "minish.h"

int builtin_exit (int argc, char ** argv){

    int arg;
    if (argv[1] == NULL) arg = globalstatret;
    else arg = atoi(argv[1]);
    
    exit(arg);

    return arg;
}
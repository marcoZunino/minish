#include <stdio.h>
#include <stdlib.h>
#include "minish.h"

int builtin_exit (int argc, char ** argv){

    int status;
    
    if (argv[1] == NULL){
        status = globalstatret;
    } else {
        status = atoi(argv[1]);
    }
    
    write_history_file();
    exit(status);

    return status;
}
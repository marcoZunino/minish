#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minish.h"

int builtin_pid(int argc, char ** argv) {

    int status = 0;         // siempre tiene exito
    pid_t pid;
    pid = getpid(); 
    printf("Identificador del proceso: %d\n", pid);
    return status;
}
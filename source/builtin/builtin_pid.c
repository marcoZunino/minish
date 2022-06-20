#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minish.h"

int builtin_pid(int argc, char ** argv) {
       
    pid_t pid;
    pid = getpid(); 
    printf("Identificador del proceso: %d\n", pid);     // muestra el process id del shell
    return 0;                                           // siempre tiene exito
}
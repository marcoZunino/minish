#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minish.h"

int builtin_pid(int argc, char ** argv) {
       
    pid_t pid;
    pid = getpid();                                     // obtiene el process id del shell
    printf("Process ID: %d\n", pid); 
    return 0;                                           // siempre tiene exito
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <error.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int linea2argv (char *linea, int argc, char **argv){
    argv[0] = strtok(linea, " \t");
    if (argv[0] == NULL){
        return 0;
    }
    int i;
    for (i = 1; i<=argc && argv[i]!=NULL; i++){
        argv[i] = strtok(NULL, " \t");
    }
    return i;
}
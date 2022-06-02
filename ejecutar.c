#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <error.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "minish.h"

int ejecutar(int argc, char **argv){
    int status;
    // fprintf(stderr, "Will execute command %s\n", argv[0]);
        
    if (strcmp(argv[0], "exit") == 0) {
        status = builtin_exit (argc, argv);
    }
    else if (strcmp(argv[0], "help") == 0){
        status = builtin_help (argv[1]);
    }
    else if (strcmp(argv[0], "history") == 0){
        status = builtin_history (argc, argv);
    }
    else if (strcmp(argv[0], "status") == 0){
        status = builtin_status (argc, argv);
    }
    else if (strcmp(argv[0], "cd") == 0){
        status = builtin_cd (argc, argv);
    }
    else if (strcmp(argv[0], "dir") == 0){
        status = builtin_dir (argc, argv);
    }
    else if (strcmp(argv[0], "help") == 0){
        status = builtin_help (argv[1]);
    }
    else if (strcmp(argv[0], "getenv") == 0){
        status = builtin_getenv (argc, argv);
    }
    else if (strcmp(argv[0], "gid") == 0){
        status = builtin_gid (argc, argv);
    }
    else if (strcmp(argv[0], "setenv") == 0){
        status = builtin_setenv (argc, argv);
    }
    else if (strcmp(argv[0], "pid") == 0){
        status = builtin_pid (argc, argv);
    }
    else if (strcmp(argv[0], "uid") == 0){
        status = builtin_uid (argc, argv);
    }
    else if (strcmp(argv[0], "unsetenv") == 0){
        status = builtin_unsetenv (argc, argv);
    }
    else {
        status = externo (argc, argv);
    }

    return status;
}
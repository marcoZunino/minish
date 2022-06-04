#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "minish.h"

int ejecutar(int argc, char **argv){
    int status = 0; // = valor por defecto
    // fprintf(stderr, "Will execute command %s\n", argv[0]);

    struct builtin_struct b;
    for (int i=0; (b = builtin_arr[i]).cmd != NULL; i++) {
        if (strcmp(argv[0], b.cmd) == 0) {
            status = b.func(argc, argv);
            break;
        }
    }
    if (b.cmd == NULL) status = externo(argc, argv);

    /*
    if (strcmp(argv[0], "exit") == 0) {
        status = builtin_exit (argc, argv);
    }
    else if (strcmp(argv[0], "help") == 0) {
        status = builtin_help (argc, argv);
    }
    else if (strcmp(argv[0], "history") == 0) {
        status = builtin_history (argc, argv);
    }
    else if (strcmp(argv[0], "status") == 0) {
        status = builtin_status (argc, argv);
    }
    else if (strcmp(argv[0], "cd") == 0) {
        status = builtin_cd (argc, argv);
    }
    else if (strcmp(argv[0], "dir") == 0) {
        status = builtin_dir (argc, argv);
    }
    else if (strcmp(argv[0], "getenv") == 0) {
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
    */

    return status;
}
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include "minish.h"

int builtin_cd (int argc, char ** argv) {

    int status = 0;
    if (argc == 1) {
        char * home = getenv("HOME");
        if (home != NULL) {
            status = chdir(home);
            //setenv("PWD", , 1);
        }
    } else if (strcmp(argv[1], "-") == 0){
        //status = chdir();
    } else {
        status = chdir(argv[1]);
        if (status == -1) {
            error(0, errno, "minishell: cd %s", argv[1]);
            //printf("minishell: cd: %s: No such file or directory\n", argv[1]);
        }
    }

    //setear PWD
    return status;
}
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
        } else {
            printf("error\n");
            return -1;
        }
    } else if (argc == 2) {
        if (strcmp(argv[1], "-") == 0) {
            status = chdir("..");
        } else {
            status = chdir(argv[1]);
            if (status == -1) {
                error(0, errno, "error cd %s", argv[1]);
            }
        }

        if (status == 0) {
            char *pwd = NULL;
            pwd = getcwd(pwd, MAXLINE);
            setenv("PWD", pwd, 1);
        }

    return status;
}
}
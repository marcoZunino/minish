#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <sys/types.h>
#include "minish.h"

int builtin_uid (int argc, char ** argv) {

    int status = 0;
    uid_t userid = getuid();                 // es siempre exitosa
    struct passwd * p = getpwuid(userid);

    if (p == 0){
        printf("Ha ocurrido un error\n");
        status = -1;
    }

    printf("User ID: %i\n", userid);
    printf("User name: %s\n", p->pw_name);

    return status;
}
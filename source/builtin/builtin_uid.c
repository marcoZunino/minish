#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <sys/types.h>
#include "minish.h"

int builtin_uid (int argc, char ** argv) {

    uid_t userid = getuid();
    struct passwd * p = getpwuid(userid);

    printf("User ID: %i\n", userid);
    printf("User name: %s\n", p->pw_name);

    return 0;
}
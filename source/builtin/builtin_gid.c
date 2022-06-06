#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "minish.h"

int builtin_gid (int argc, char ** argv) {

    int status = 0;
    gid_t groupid = getgid();
    gid_t groups[MAXWORDS] = { 0 };
    
    int obtener_grupos = getgroups(MAXWORDS, groups);
    if (obtener_grupos == -1) {
        printf("Ha ocurrido un error\n");
        status = 1;
    }
    printf("Group ID: %i\n", groupid);
    printf("Secondary groups IDs:\n");
    for (int i = 0; groups[i]!=0; i++) {
        if (groups[i]!=groupid) printf("\t%i\n", groups[i]);
    }

    return status;
}
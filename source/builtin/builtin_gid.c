#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <errno.h>
#include <error.h>
#include "minish.h"

int builtin_gid (int argc, char ** argv) {

    gid_t groupid = getgid();                   // obtiene la identidad del grupo
    gid_t groups[MAXWORDS] = { 0 };             

    struct passwd * p = getpwuid(getuid());     // devolverá un puntero a una estructura passwd
                                                // definida en <pwd.h> con una entrada coincidente si se encuentra

    if (p == NULL){                             // devolverá un puntero nulo si no se encuentra la entrada solicitada o si se produce un error
        error(0, errno, "error gid");
        return 1;
    }
    
    if (getgroups(MAXWORDS, groups) == -1) {    //obtener grupos secundarios
        error(0, errno, "error gid");
        return 1;
    }

    printf("Real Group: %i (%s)\n", groupid, p->pw_name);
    printf("Other Groups: ");
    for (int i = 0; groups[i]!=0; i++) {
        if (groups[i] != groupid) printf("%i ", groups[i]); //se imprimen grupos secundarios
    }
    printf("\n");

    return 0;
}
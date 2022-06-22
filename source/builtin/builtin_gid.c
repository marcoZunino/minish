#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include "minish.h"

int builtin_gid (int argc, char ** argv) {

    gid_t groupid = getgid();                   // obtiene la identidad del grupo
    gid_t groups[MAXWORDS] = { 0 };             

    struct passwd * p = getpwuid(getuid());     // devolverá un puntero a una estructura passwd con la estructura 
                                                // definida en <pwd.h> con una entrada coincidente si se encuentra

    if (p == NULL){                             // devolverá un puntero nulo si no se encuentra la entrada solicitada o si se produce un error
        //printf("Ha ocurrido un error\n");
        return 1;
    }
    
    if (getgroups(MAXWORDS, groups) == -1) {    //obtener grupos secundarios
        //printf("Ha ocurrido un error\n");
        return 1;
    }

    printf("Real Group: %i (%s)\n", groupid, p->pw_name);
    printf("Other Groups: ");
    for (int i = 0; groups[i]!=0; i++) {
        if (groups[i] != groupid) printf("%i ", groups[i]);
    }
    printf("\n");

    return 0;
}
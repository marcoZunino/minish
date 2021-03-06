#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <error.h>
#include "minish.h"

int builtin_uid (int argc, char ** argv) {

    uid_t userid = getuid();                 // obtiene la identidad del usuario. Es siempre exitosa
    struct passwd * p = getpwuid(userid);    // devolverá un puntero a una estructura passwd con la estructura 
                                             // definida en <pwd.h> con una entrada coincidente si se encuentra

    if (p == NULL){                          // devolverá un puntero nulo si no se encuentra la entrada solicitada o si se produce un error
        error(0, errno, "error uid");
        return 1;
    }

    printf("User ID: %i\n", userid);        // muestra el userid
    printf("User name: %s\n", p->pw_name);  // muestra el nombre del usuario

    return 0;
}
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include "minish.h"

void update_env (char *old) {
    char *pwd = NULL;
    pwd = getcwd(pwd, MAXLINE);    
    setenv("PWD", pwd, 1);          // actualiza PWD con el corriente
    setenv("OLDPWD", old, 1);       // actualiza OLDPWD con el anterior
}

int builtin_cd (int argc, char ** argv) {

    int status = 0;
    char *oldpwd = NULL;
    oldpwd = getcwd(oldpwd, MAXLINE);     // obtiene el directorio corriente

    if (argc == 1) {                      // si cd no tiene parámetros vuelve al directorio HOME
        char * home = getenv("HOME");
        if (home != NULL) {
            status = chdir(home);         // cambia del directorio corriente al especificado en la ruta
        } else {
            printf("error\n");            // significa que no esta definida la variable HOME
            return 1;
        }
        if (status == 0) {
            update_env(oldpwd);           // actualiza variable de ambiente
        }
    } else if (argc == 2) {               // si 'cd -' vuelve al directorio anterior (OLDPWD)
        if (strcmp(argv[1], "-") == 0) {

            char * prev = getenv("OLDPWD");
            if (prev != NULL) {
                status = chdir(prev);
            } else {
                printf("error\n");        // no esta definida la variable OLDPWD
                return 1;
            }

        } else {                          // si 'cd [DIR]' cambia al directorio DIR
            status = chdir(argv[1]);    
            if (status == -1) {
                error(0, errno, "error cd %s", argv[1]); // no existe el directorio
            }
        }

        if (status == 0) {
            update_env(oldpwd);
        }
        return status;

    } else {
        //error, pocos argumentos
        return 1;
    }
}
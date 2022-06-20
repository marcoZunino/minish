#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include "minish.h"

int get_files(char * dir_name, char ** file_list) {
    DIR * d = opendir(dir_name);
    if (d == NULL) {
        return -1;
    } else {
        struct dirent * dir;
        for (int i = 0; i < MAXWORDS && (dir = readdir(d)) != NULL; i++) {
            file_list[i] = dir->d_name;
        }
        closedir(d);
    }
    return 0;
}


int builtin_dir (int argc, char ** argv) {

    int status = 0;
    if (argc == 1) {// sin argumentos muestra la lista de archivos del directorio corriente
        struct dirent * dir;
        DIR * d = opendir(".");
        while ((dir = readdir(d)) != NULL) {
            printf("%s\n", dir->d_name);
        }
        closedir(d);

        // char * files[MAXWORDS] = {NULL};
        // status = get_files(".", files);
        //imprimir los archivos

    } else if (argc == 2) { // con un unico argumento, comprobar si es un directorio
        DIR * d = opendir(argv[1]);

        if (d == NULL) {
            struct dirent * c;
            d = opendir(".");
            while ((c = readdir(d)) != NULL) {
                if (strstr(c->d_name, argv[1]) != NULL) {
                    printf("%s\n", c->d_name);
                }
            }
        } else {
            struct dirent * c;
            while ((c = readdir(d)) != NULL) {
                printf("%s\n", c->d_name);
            }
        }
        closedir(d);

        // } else {
        //     struct dirent * current = get_dir(".");
        //     //filtrar archivos por argv[1]

        // }

    } else if (argc == 3) { //con dos argumentos, directorio/texto
        DIR * d = opendir(argv[1]);

        if (d == NULL) {
            //error no existe directorio
            return -1;
        }
        struct dirent * c;
        while ((c = readdir(d)) != NULL) {
            if (strstr(c->d_name, argv[2]) != NULL) {
                printf("%s\n", c->d_name);
            }
        }
        closedir(d);
        //struct dirent * dir = get_dir(argv[1]);
        //filtrar archivos por argv[2]

    } else {
        //error de argumentos
    }

    


    return status;
}
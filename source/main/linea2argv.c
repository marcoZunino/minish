#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <error.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "minish.h"

int linea2argv(char* linea, int argc, char** argv) {
    
    int count = 0;                                          // variable para contar la cantidad de variables encontradas
    
    if (linea == NULL || argc < 2 || argv == NULL) {        // si linea o argv es null o argc es menor a 2 se retorna 0
        return 0;
    }
    
    for (int i = 0, j = 0; linea[i] != '\0'; i++) {
        if (linea[i] == ' ' || linea[i] == '\t' || linea[i+1] == '\0') {        
            if (count == argc) break;
            if (i != 0) {
                argv[count] = strndup(linea + j, i-j);
                count++;
            }

            while (linea[i+1]!='\0' && (linea[i+1]==' ' || linea[i+1]=='\t' || linea[i+1]=='\n') ) i++;
            j = i+1;
        }
    }
    argv[count] = NULL;

    return count;           // devuelve la cantidad de palabras encotradas

}
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
    
    for (int i = 0, j = 0; linea[i] != '\0'; i++) {     //se recorre la linea
        if (linea[i] == ' ' || linea[i] == '\t' || linea[i+1] == '\0') {
        //se chequea el caracter, si es 'normal' se pasa a la siguiente iteracion
            if (count == argc) break;   //ya se llego a la cantidad maxima de argumentos

            if (i != 0) { //en el caso i=0 se sigue en busca del primer caracter 'normal'
                argv[count] = strndup(linea + j, i-j); //se copian los caracteres desde el ultimo 'normal'
                count++;  //se suma un argumento
            }

            while (linea[i+1]!='\0' && (linea[i+1]==' ' || linea[i+1]=='\t' || linea[i+1]=='\n') ) i++;
                //se saltea si hay espacios, tabuladores o enters
            j = i+1;    //linea[j] es el proximo caracter 'normal' -> se fija el inicio del argumento siguiente
        }
    }
    argv[count] = NULL;     //se fija en NULL el ultimo

    return count;           // devuelve la cantidad de palabras encontradas

}
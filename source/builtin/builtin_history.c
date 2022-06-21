#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "minish.h"
#define DEFAULT_COMMANDS 10

// void strcat_c (char *str, char c) {
//     int i=0;
//     for (;*str;str++,i++);
//     *str++ = c;
//     *str++ = '\0';
// }

// int getnlines (char ** buffer, char * path, int max) {

//     FILE * history = fopen(path, "r");
    
//     if (history == NULL) {
//         return 1;
//     }
        
//     char line[MAXLINE];
//     int i = 0;
//     int p = 0;
//     char c;
//     while ((c = fgetc(history)) != EOF && i < max) {

//         if (c == '\n') {
//             buffer[i] = strdup(line);
//             line[0] = '\0';
//             printf("line: %s\n", line);
//             p = 0;
//             i++;
//         } else {
//             line[p] = c;
//             p++;
//         }
//     }
//     fclose(history);

//     return 0;

// }

int builtin_history (int argc, char ** argv) {

    int n = DEFAULT_COMMANDS;
    if (argc == 1) {
    } else if (argc == 2) {
        n = atoi(argv[1]);
        // CHEQUEAR ERROR DE CASTEO
    } else {
        // error: demasiados argumentos
        return 1;
    }

    struct history_entry * entry = history_arr->last;
    if (entry == NULL) {
        return 1;
    }
    for (int c = 0; c < n && entry->prev != NULL; entry = entry->prev, c++) {
        printf("%i: %s", c, entry->command);
    }

    return 0;
}
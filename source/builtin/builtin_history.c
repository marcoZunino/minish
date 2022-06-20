#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "minish.h"
#define DEFAULT_COMMANDS 10

void strcat_c (char *str, char c) {
    int i=0;
    for (;*str;str++,i++);
    *str++ = c;
    *str++ = '\0';
}

int getnlines (char ** buffer, char * path, int max) {

    FILE * history = fopen(path, "r");
    
    if (history == NULL) {
        return -1;
    }
        
    char line[MAXLINE];
    int i = 0;
    int p = 0;
    char c;
    while ((c = fgetc(history)) != EOF && i < max) {

        if (c == '\n') {
            buffer[i] = strdup(line);
            line[0] = '\0';
            printf("line: %s\n", line);
            p = 0;
            i++;
        } else {
            line[p] = c;
            p++;
        }
    }
    fclose(history);

    return 0;

}

int builtin_history (int argc, char ** argv) {
    
    int status = 0;

    int n = DEFAULT_COMMANDS;
    if (argc == 1) {
    } else if (argc == 2) {
        n = atoi(argv[1]);
        // chequear error de casteo
    } else {
        // error: demasiados argumentos
        return -1;
    }

    char * lines[n];
    int entry_number;
    if (history_arr->qty <= n) {
        entry_number = history_arr->qty;
    } else {
        entry_number = n;
    }
    
    for (struct history_entry * entry = history_arr->first; entry_number >= 0; entry_number--, entry = entry->next) {
        lines[entry_number] = entry->command;
    }

    if (n > history_arr->qty) {

    // char path[MAXLINE];
    // strncpy(path, getenv("HOME"), MAXLINE);
    // strcat(path, "/");
    // strcat(path, HISTORY_FILE);
    
    // char ** lines = malloc(sizeof(char*) * n);
    
    // status = getnlines(lines, path, n);
    
    // if (status == 0) {
    //     // for (int i = n - 1; i >= 0; i--) {
    //     //     if (lines[i] != NULL) {
    //     //         printf("%i: %s\n", i, lines[i]);
    //     //         free(lines[i]);
    //     //     }
    //     // }
    //     printf("n: %i\n", n);
    //     for (int i=0; i<n; i++) {
    //         if (lines[i]!=NULL) {
    //             printf("%i:\n%s\n", i, lines[i]);
    //             free(lines[i]);
    //         }
    //     }

    // }
    // free(lines);
    }
    
    //printf("n: %i\n", n);
    for (int i=0; i<n; i++) {
        if (lines[i]!=NULL) {
            printf("%i: %s", i, lines[i]);
        }
    }

    return status;
}
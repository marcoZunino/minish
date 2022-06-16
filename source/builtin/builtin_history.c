#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "minish.h"
#define DEFAULT_COMMANDS 10

int builtin_history (int argc, char ** argv) {

    int chars;
    if (argc == 1) {
        chars = DEFAULT_COMMANDS;
    } else {
        chars = atoi(argv[1]);
    }

    char path[MAXLINE];
    strncpy(path, getenv("HOME"), MAXLINE);
    strcat(path, "/");
    strcat(path, HISTORY_FILE);
    
    FILE * history = fopen(path, "r");
    if (history == NULL) {
        return -1;
    } else {
        int i = chars;
        char c;
        
        printf("%i: ", i);
        i--;
        while ((c = fgetc(history)) != EOF && i >= 0) {
            printf("%c", c);
            if (c == '\n' && i >= 0) {
                printf("%i: ", i);
                i--;
            }
        }
        fclose(history);
        return 0;
    }

}
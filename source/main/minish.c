#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <error.h>
#include <errno.h>
#include "minish.h"

void prompt(char *ps) {
    // ps is the prompt string
    fprintf(stderr, "(%s) ^D to exit > ", ps);
}

void sigint_handler(int signum) {             // the handler for SIGINT
    fprintf(stderr, "Interrupt! (signal number %d)\n", signum);
}


void add_history_entry(char *cmd) {
    if (cmd != NULL) {
        struct history_entry * new = (struct history_entry *) malloc(sizeof(struct history_entry));
        new->command = strdup(cmd);
        new->next = NULL;

        if (history_arr->qty == 0) {
            history_arr->first = new;
            new->prev = NULL;
            history_arr->last = new;
        } else {
            new->prev = history_arr->last;
            history_arr->last->next = new;
            history_arr->last = new;
        }

        history_arr->qty ++;
    }
}

void clean_list(struct history_list *list){
    
    struct history_entry *entry = list->first;
    //list->first = NULL;
    for (struct history_entry *nxt = entry->next; entry!=NULL; entry=nxt) {
        nxt = entry->next;
        entry->next = NULL;
        entry->prev = NULL;
        free(entry->command);
        free(entry);

    }
    //list->last = NULL;

}


void write_history_file(int history_length) {
    
    char path[MAXLINE];
    strncpy(path, getenv("HOME"), MAXLINE);
    strcat(path, "/");
    strcat(path, HISTORY_FILE);
    
    FILE *history = fopen(path, "a");
    if (history == NULL) {
        //ERROR
        return;
    }

    struct history_entry *entry = history_arr->first;

    struct history_entry *nxt = entry->next;
    for (int p = 0; entry != NULL; entry = nxt, p++) {
        nxt = entry->next;
        if (p >= history_length) {
            fputs(entry->command, history);
        }
    }
    fclose(history);

    clean_list(history_arr);
}

void load_history() {

    char path[MAXLINE];
    strncpy(path, getenv("HOME"), MAXLINE);
    strcat(path, "/");
    strcat(path, HISTORY_FILE);

    FILE * history = fopen(path, "r");
    if (history == NULL) {
        //ERROR
        return;
    }

    char line[MAXLINE] = {0};
    int p = 0;
    char c;
    while ((c = fgetc(history)) != EOF) {
        line[p] = c;
        line[p+1] = '\0';
        p++;

        if (c == '\n') {
            add_history_entry(line);
            line[0] = '\0';
            p = 0;
        }
    }
    fclose(history);
}


struct builtin_struct builtin_arr[] = {
        {"exit", builtin_exit, HELP_EXIT},
        {"help", builtin_help, HELP_HELP},
        {"history", builtin_history, HELP_HISTORY},
        {"status", builtin_status, HELP_STATUS},
        {"cd", builtin_cd, HELP_CD},
        {"dir", builtin_dir, HELP_DIR},
        {"getenv", builtin_getenv, HELP_GETENV},
        {"gid", builtin_gid, HELP_GID},
        {"setenv", builtin_setenv, HELP_SETENV},
        {"pid", builtin_pid, HELP_PID},
        {"uid", builtin_uid, HELP_UID},
        {"unsetenv", builtin_unsetenv, HELP_UNSETENV},
        {NULL, NULL, NULL}
};


struct history_list history_array = {NULL, NULL, 0};
struct history_list *history_arr = &history_array;

int globalstatret = 0; // = valor por defecto

int
main () {

    if (getenv("HOME") == NULL) {
        // ./minish: variable de ambiente HOME no existe - se usará history en /usr/local/bin
        // ./minish: no se puede openat archivo history: .minish_history: Permission denied
        error(0, errno, "./minish: variable de ambiente HOME no existe - se usará history en /usr/local/bin\n");
        exit(-1);
    }

    load_history();
    int history_length = history_arr->qty;

    char line[MAXLINE];

    char *dirname = NULL;
    
    struct sigaction oldact, newact;

    sigaction(SIGINT, NULL, &newact);         // the  previous action for SIGINT is saved in oldact
    newact.sa_handler = sigint_handler;
    sigaction(SIGINT, &newact, NULL);           // set SIGINT handler for loop


    for (;;) {

        prompt(getcwd(dirname, MAXLINE));   //prompt, current directory

        if (fgets(line, MAXLINE, stdin) == NULL) {  // EOF

            if (feof(stdin)) {
                break;      // normal EOF, break loop
            } else {
                continue;   // not EOF, read system call was interrupted, continue loop
            }
        }

        char *argv[MAXWORDS] = {NULL};
        int argc = linea2argv(line, MAXWORDS - 1, argv);
        if (argc == 0) {
            continue;
        }

        add_history_entry(line);

        globalstatret = ejecutar(argc, argv);

    }

    write_history_file(history_length);
    fputc('\n', stderr);
    exit(globalstatret);
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <error.h>
#include <errno.h>
#include "minish.h"

void
prompt(char *ps) {
    // ps is the prompt string
    fprintf(stderr, "(%s) ^D to exit > ", ps);
}

void
sigint_handler(int signum) {             // the handler for SIGINT
    fprintf(stderr, "Interrupt! (signal number %d)\n", signum);
}

void
add_history_entry(char *cmd) {
    if (cmd != NULL) {
        struct history_entry * new = (struct history_entry *) malloc(sizeof(struct history_entry));
        new->command = strdup(cmd);
        new->next = NULL;

        struct history_entry * end = history_arr->first;
        if (end != NULL) {
            for (; end->next!=NULL; end = end->next);
            end->next = new;
        } else {
            history_arr->first = new;
        }
        history_arr->qty ++;
    }
}

void
write_history_file() {
    char path[MAXLINE];
    strncpy(path, getenv("HOME"), MAXLINE);
    strcat(path, "/");
    strcat(path, HISTORY_FILE);
    
    FILE *history = fopen(path, "a");
    struct history_entry *entry = history_arr->first;
    for (struct history_entry *next; entry != NULL; entry = next) {
        next = entry->next;
        fputs(entry->command, history);
        free(entry);
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


//struct history_list *history_arr = (struct history_list *) malloc(sizeof(struct history_list));
struct history_list history_array = {NULL, 0};
struct history_list *history_arr = &history_array;
// history_arr->first = NULL;
// history_arr->qty = 0;


int globalstatret = 0; // = valor por defecto

int
main () {

    if (getenv("HOME") == NULL) {
        // ./minish: variable de ambiente HOME no existe - se usará history en /usr/local/bin
        // ./minish: no se puede openat archivo history: .minish_history: Permission denied
        error(0, errno, "./minish: variable de ambiente HOME no existe - se usará history en /usr/local/bin\n");
        exit(-1);
    }

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

    write_history_file();
    fputc('\n', stderr);
    exit(globalstatret);
}
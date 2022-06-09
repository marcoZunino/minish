#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
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

int globalstatret = 0; // = valor por defecto

int
main () {

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

        globalstatret = ejecutar(argc, argv);

    }

    fputc('\n', stderr);
    exit(EXIT_SUCCESS); //exit(globalstatret)
}
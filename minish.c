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


#define MAXLINE 1024
#define MAXARG 100
#define HELP_CD "Comando cd hace ..."

void
prompt(char *ps) {
    // ps is the prompt string
    fprintf(stderr, "(%s) ^D to exit > ", ps);
}

void
sigint_handler(int signum) {                    // the handler for SIGINT
    fprintf(stderr, "Interrupt! (signal number %d)\n", signum);
}

struct builtin_struct builtin_arr[] = {
        {"cd", builtin_cd, HELP_CD },
        {"exit", builtin_exit, HELP_EXIT},
        {"", builtin_}

        { "uid", builtin_uid, HELP_UID },
        { NULL, NULL, NULL }
    };

int
main(int argc, char *argv[]) {
    // Escribir prompt string en standard error??
    
    char line[MAXLINE];
    // char *progname = argv[0];
    char *dirname = NULL;
    dirname = getcwd(dirname, MAXLINE);
    
    struct sigaction oldact, newact;

    sigaction(SIGINT, NULL, &newact);           // the  previous action for SIGINT is saved in oldact
    newact.sa_handler = sigint_handler;
    sigaction(SIGINT, &newact, NULL);           // set SIGINT handler for loop


    for (;;) {
        prompt(dirname);
        if (fgets(line, MAXLINE, stdin) == NULL) {  // EOF
           
            if (feof(stdin)) {
                break;      // normal EOF, break loop
            } else {
                continue;   // not EOF, read system call was interrupted, continue loop
            }
        }

        char *args[MAXARG] = {NULL};

        int argc = linea2argv(line, MAXARG - 1, argv);

        int status = ejecutar(int argc, char **argv);

        // actualizar status

    }

    fputc('\n', stderr);
    fprintf(stderr, "Exiting %s ...\n", progname);
    exit(EXIT_SUCCESS);
}
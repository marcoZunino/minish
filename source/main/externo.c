#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "minish.h"

int externo (int argc, char ** argv) {

    struct sigaction oldact, newact;

    sigaction(SIGINT, NULL, &newact);           // the  previous action for SIGINT is saved in oldact
    newact.sa_handler = sigint_handler;
    sigaction(SIGINT, &newact, NULL);           // set SIGINT handler for loop

    pid_t pid;
    int status;


    sigaction(SIGINT, NULL, &oldact);           // the  previous action for SIGINT is saved in oldact
    newact = oldact;

    if ((pid = fork()) < 0) {                   // fork error, i.e. too many processes
        
        error(0, errno, "fork error\n");

    } else if (pid == 0) {                      //child
        
        newact.sa_handler = SIG_DFL;
        sigaction(SIGINT, &newact, NULL);

        execvp(argv[0], argv);                  // if successful, child will go on with new executable
        error(EXIT_FAILURE, errno, "execvp error\n");   // if exec not successful, just exit child

    } else {                                    //parent (shell) process
        newact.sa_handler = SIG_IGN;
        sigaction(SIGINT, &newact, NULL);       // ignore SIGINT while waiting
        waitpid(pid, &status, 0);
        
        sigaction(SIGINT, &oldact, NULL);       // restore SIGINT when child finishes

    }

    return status;
}
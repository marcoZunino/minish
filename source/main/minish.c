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


void add_history_entry(char *cmd) { //agregar nodo a la lista de history
    if (cmd != NULL) {
        struct history_entry * new = (struct history_entry *) malloc(sizeof(struct history_entry));
        new->command = strdup(cmd); //se copia la linea
        new->next = NULL;

        if (history_arr->qty == 0) {    //primer nodo
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

void clean_list(struct history_list *list){ //se borra la lista y se libera la memoria usada
    
    struct history_entry *entry = list->first;
    //list->first = NULL;
    for (struct history_entry *nxt = entry->next; entry!=NULL; entry=nxt) { //se recorre la lista
        nxt = entry->next;
        entry->next = NULL;     //no debe liberarse este puntero ya que todos los nodos seran liberados con free(entry)
        entry->prev = NULL;     //
        free(entry->command);
        free(entry);

    }
    //list->last = NULL;

}

void write_history_file(int history_length) {   //actualizacion del archivo del history
    
    char path[MAXLINE];     //path al archivo del history
    strncpy(path, getenv("HOME"), MAXLINE);
    strcat(path, "/");
    strcat(path, HISTORY_FILE);
    
    FILE *history = fopen(path, "a");   //se abre el archivo en modo escritura al final (append)
                                        // o se crea si no existia
    if (history == NULL) {
        //ERROR
        return;
    }

    struct history_entry *entry = history_arr->first;

    struct history_entry *nxt = entry->next;
    for (int p = 0; entry != NULL; entry = nxt, p++) { //se recorre la lista
        nxt = entry->next;
        if (p >= history_length) {  //se empieza a escribir al llegar a la cantidad de comandos ya escritos
            fputs(entry->command, history); //se escribe al final del archivo
        }
    }
    fclose(history);    //se cierra el archivo

    clean_list(history_arr);       //se libera la memoria dinamica de la lista
}

int load_history() {

    char path[MAXLINE];     //path al archivo del history
    strncpy(path, getenv("HOME"), MAXLINE);
    strcat(path, "/");
    strcat(path, HISTORY_FILE);

    FILE * history = fopen(path, "r");     //se abre el archivo en modo lectura desde el principio
    if (history == NULL) {
        //ERROR
        return 1;
    }

    char line[MAXLINE] = {0};   //buffer para cargar los comandos
    int p = 0;  //indice dentro del buffer
    char c;
    while ((c = fgetc(history)) != EOF) {   //se recorre el archivo por caracteres
        line[p] = c;        //se va escribiendo el comando en el buffer
        line[p+1] = '\0';   //se fija un null provisorio al final
        p++;

        if (c == '\n') {    //fin del comando
            add_history_entry(line);
            line[0] = '\0'; //se resetea la linea
            p = 0;  //se vuelve a comenzar del principio del buffer
        }
    }
    fclose(history);
    return 0;
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

struct history_list history_array = {NULL, NULL, 0};    //se crea la lista del history
struct history_list *history_arr = &history_array;      //se guarda puntero a la lista
int history_length = 0; //se inicializa

int globalstatret = 0; // valor por defecto

int
main () {

    if (getenv("HOME") == NULL) {
        // ./minish: variable de ambiente HOME no existe - se usará history en /usr/local/bin
        // ./minish: no se puede openat archivo history: .minish_history: Permission denied
        error(0, errno, "./minish: variable de ambiente HOME no existe - se usará history en /usr/local/bin\n");
        exit(1);
    }    

    if (load_history() == 1) {
        error(0, errno, "./minish: error con el arhivo history\n");
        exit(1);
    }
    history_length = history_arr->qty;  //se guarda la cantidad de comandos ya existentes en history

    char line[MAXLINE];
    
    struct sigaction oldact, newact;

    sigaction(SIGINT, NULL, &newact);         // the  previous action for SIGINT is saved in oldact
    newact.sa_handler = sigint_handler;
    sigaction(SIGINT, &newact, NULL);           // set SIGINT handler for loop

    char *dirname = NULL;

    for (;;) {

        prompt(getcwd(dirname, MAXLINE));   //prompt, current directory

        if (fgets(line, MAXLINE, stdin) == NULL) {  // EOF

            if (feof(stdin)) {
                break;      // normal EOF, break loop
            } else {
                continue;   // not EOF, read system call was interrupted, continue loop
            }
        }

        char *argv[MAXWORDS] = {NULL};      //se crea array para argumentos
        int argc = linea2argv(line, MAXWORDS - 1, argv);    //separa la linea en argumentos
        if (argc == 0) {
            continue;   //entrada vacia, pide otra linea
        }

        add_history_entry(line); //append a la lista de history con la linea leida

        globalstatret = ejecutar(argc, argv);   //ejecucion de comando, devuelve el status resultante

    }

    write_history_file(history_length); //se actualiza el archivo de history
    fputc('\n', stderr);
    exit(globalstatret);    //termina el minishell con el status del ultimo comando ejecutado
}
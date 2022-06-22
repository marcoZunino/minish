#include <stdio.h>
#include "minish.h"

int builtin_status (int argc, char ** argv) {
    printf("%i\n", globalstatret);              // muestra el status de retorno del último comando ejecutado
    return 0;
}
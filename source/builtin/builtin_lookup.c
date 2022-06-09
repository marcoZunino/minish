#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minish.h"

struct builtin_struct * builtin_lookup (char * cmd) {

    struct builtin_struct * b;
    for (b = builtin_arr; b->cmd != NULL; b++) {
        if (strcmp(cmd, b->cmd) == 0) return b;
    }

    return NULL;

}
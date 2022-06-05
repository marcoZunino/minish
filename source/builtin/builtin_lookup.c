#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minish.h"

struct builtin_struct * builtin_lookup (char * cmd) {

    struct builtin_struct * b;
    for (int i=0; (b = &builtin_arr[i])->cmd != NULL; i++) {
        if (strcmp(cmd, b->cmd) == 0) break;
    }
    if (b->cmd == NULL) return NULL;

    return b;

}
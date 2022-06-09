#include <stdio.h>
#include "minish.h"

int builtin_status (int argc, char ** argv) {
    printf("%i\n", globalstatret);
    return 0;
}
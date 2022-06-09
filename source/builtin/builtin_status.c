#include <stdio.h>
#include "minish.h"

int builtin_status (int argc, char ** argv) {
    printf("status = %i", globalstatret);
    return 0;
}
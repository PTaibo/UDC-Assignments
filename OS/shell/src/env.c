#include "env.h"
#include <stdlib.h>
#define MAX_ARGS 4800

static char** main_arg3 = NULL;
static int args = 0;
static char* argv[MAX_ARGS] = {NULL};

void set_mainarg3 (char** src)
{
    main_arg3 = src;
}

char** get_mainarg3 ()
{
    return main_arg3;
}

void set_args (int arg)
{
    args = arg;
}

int get_args ()
{
    return args;
}

void set_argv (char* arg[])
{
     for (int i = 0; i < get_args(); i++) {
        argv[i] = arg[i];
        if (arg[i] == NULL) {
            break;
        }
    }
}

char** get_argv ()
{
    return argv;
}


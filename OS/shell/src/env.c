#include "env.h"
#include <stdlib.h>

static char** main_arg3 = NULL;

void set_mainarg3 (char** src)
{
    main_arg3 = src;
}

char** get_mainarg3 ()
{
    return main_arg3;
}

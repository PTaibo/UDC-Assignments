/*
 * Name: Siyuan He              Login: siyuan.he
 * Name: Paula Taibo Suárez     Login: p.taibo
 */

#include "env.h"
#include <stdlib.h>

static char** main_arg3 = NULL;
static int size = 0;

void set_mainarg3 (char** src)
{
    main_arg3 = src;
    for (size = 0; main_arg3[size] != NULL; size++);
}

char** get_mainarg3 ()
{
    return main_arg3;
}

int get_mainarg3Size()
{
    return size;
}

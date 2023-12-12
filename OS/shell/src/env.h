#pragma once

#include <stdlib.h>

char** environment = NULL;

void set_environment(char** src)
{
    environment = src;
}

char** get_environment()
{
    return environment;
}

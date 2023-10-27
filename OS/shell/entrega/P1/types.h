#pragma once

#define MAX_COMMAND_SIZE 200
#define UNUSED __attribute__((unused)) // Gets rid of unused parameter warnings

struct cmd {
    char *name;
    void (*funct)(int, char**);
};

struct open_flags {
    char* name;
    int flag;
};


#pragma once

#include "list.h"

struct cmd {
    char *name;
    void (*funct)(int, char**, List*);
};

struct help {
    char *command;
    void (*funct)();
};

extern struct cmd valid_commands[];
extern struct cmd hist_commands[];
extern struct cmd file_commands[];
extern struct help help_pages[];

extern List history;


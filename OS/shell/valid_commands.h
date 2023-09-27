#pragma once

struct cmd {
    char *name;
    void (*funct)(int, char**);
};

struct help {
    char *command;
    void (*funct)();
};

extern struct cmd valid_commands[];
extern struct help help_pages[];


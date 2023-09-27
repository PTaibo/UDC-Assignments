#pragma once

#include "instructions.h"
#include <stdio.h>

struct cmd {
    char *name;
    void (*funct)(int, char**);
};

struct cmd valid_commands[] = {
    {"authors", cmd_authors},
    {"pid", cmd_pid},
    {"chdir", cmd_chdir},
    /* {"date", cmd_date}, */
    /* {"time", cmd_time}, */
    /* {"hist", cmd_hist}, */
    /* {"command", cmd_repeat}, */
    /* {"open", cmd_open}, */
    /* {"close", cmd_close}, */
    /* {"dup", cmd_dup}, */
    /* {"listopen", cmd_listopen}, */
    {"infosys", cmd_infosys},
    {"help", cmd_help},
    {"quit", cmd_quit},
    {"exit", cmd_quit},
    {"bye", cmd_quit},
    {NULL, NULL}
};


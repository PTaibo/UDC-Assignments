#include "valid_commands.h"
#include "instructions.h"
#include "help.h"
#include <stdlib.h>

struct cmd valid_commands[] = { 
    {"authors", cmd_authors},
    {"pid", cmd_pid},
    {"chdir", cmd_chdir},
    {"date", cmd_date},
    {"time", cmd_time},
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

struct help help_pages[] = { 
    {"authors", help_authors},
    {"pid", help_pid},
    {"chdir", help_chdir},
    {"date", help_date},
    {"time", help_time},
    {"hist", help_hist},
    {"command", help_command},
    {"open", help_open},
    {"close", help_close},
    {"dup", help_dup},
    {"listopen", help_listopen},
    {"infosys", help_infosys},
    {"quit", help_quit},
    {"exit", help_quit},
    {"bye", help_quit},
    {NULL, NULL}
};

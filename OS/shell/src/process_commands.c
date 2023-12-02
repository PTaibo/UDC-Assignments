#include "process_commands.h"

#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "list.h"
#include "help_pages.h"

DynamicList procList;

void init_proc()
{
    dynList_init(&procList);
}

void delete_procblock()
{
}

void rm_proc()
{
    dynList_clear(delete_procblock, &procList);
}

struct cmd proc_commands[] = {
    {"uid", cmd_uid},
    {"showvar", cmd_showvar},
    {"changevar", cmd_changevar},
    {"subsvar", cmd_subsvar},
    {"showenv", cmd_showenv},
    {"fork", cmd_fork},
    {"exec", cmd_exec},
    {"jobs", cmd_jobs},
    {"deljobs", cmd_deljobs},
    {"job", cmd_job},
    {NULL, NULL}
};

int check_mem_commands (int paramN, char* command[])
{
    for (int i = 0; proc_commands[i].name != NULL; i++){
        if (!strcmp(command[0], proc_commands[i].name)){
            if (!is_help_param(paramN, command))
                (*proc_commands[i].funct)(paramN, command+1);
            return 1;
        }
    }

    return 0;
}

void cmd_uid(int paramN, char **command)
{
}

void cmd_showvar(int paramN, char **command)
{
}

void cmd_changevar(int paramN, char **command)
{
}

void cmd_subsvar(int paramN, char **command)
{
}

void cmd_showenv(int paramN, char **command)
{
}

void cmd_fork(int paramN, char **command)
{
}

void cmd_exec(int paramN, char **command)
{
}

void cmd_jobs(int paramN, char **command)
{
}

void cmd_deljobs(int paramN, char **command)
{
}

void cmd_job(int paramN, char **command)
{
}


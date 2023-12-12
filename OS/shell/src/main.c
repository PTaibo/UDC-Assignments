/*
 * Name: Siyuan He              Login: siyuan.he
 * Name: Paula Taibo Suárez     Login: p.taibo
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "types.h"
#include "command_processor.h"
#include "history_commands.h"
#include "file_commands.h"
#include "mem_commands.h"
#include "env.h"

int main(UNUSED int argc,UNUSED char* argv[], char* env[])
{
    char line [MAX_COMMAND_SIZE];
    init_file_list();
    init_history();
    init_mem();
    set_mainarg3(env);

    char cwd[MAX_COMMAND_SIZE];
    getcwd(cwd, MAX_COMMAND_SIZE);
    printf("%s$ ", cwd);

    while (fgets(line, MAX_COMMAND_SIZE, stdin) != NULL){
        processCommand(line);
        getcwd(cwd, MAX_COMMAND_SIZE);
        printf("%s$ ", cwd);
    }

    return 0;
}


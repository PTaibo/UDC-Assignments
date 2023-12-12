#include <string.h>
#include <stdio.h>

#include "basic_commands.h"
#include "history_commands.h"
#include "file_commands.h"
#include "stat_commands.h"
#include "mem_commands.h"
#include "process_commands.h"
#include "help_pages.h"
#include "colors.h"
#include "types.h"
#include "external_commands.h"

int divideLine (char* line, char* command_chunks[])
{
    int i = 0;

    command_chunks[i] = strtok(line, " \n\t");

    while (command_chunks[i] != NULL)
        command_chunks[++i] = strtok(NULL, " \n\t");

    return i - 1;
}

void executeCommand (int paramN, char* command_chunks[])
{
    if (!strcmp(command_chunks[0], "help")){
        cmd_help(paramN, command_chunks+1);
    }
    else if (check_basic_commands(paramN, command_chunks));
    else if (check_history_commands(paramN, command_chunks));
    else if (check_file_commands(paramN, command_chunks));
    else if (check_stat_commands(paramN, command_chunks));
    else if (check_mem_commands(paramN, command_chunks));
    else if (check_process_commands(paramN, command_chunks));
    else
        // printf(RED "Error: " RESET_CLR "not a valid command\n");
        execute_external_command(paramN, command_chunks);
}

void processCommand (char* line){
    char* command_chunks[MAX_COMMAND_SIZE/2];
    int paramN = divideLine (line, command_chunks);
    if (command_chunks[0] == NULL)
        return;
    // To avoid infinite command repetition loops
    if (strcmp(command_chunks[0], "command")){
        add_history_entry(line);
    }
    executeCommand(paramN, command_chunks);
}


#include <string.h>
#include <stdio.h>

#include "basic_commands.h"
#include "history_commands.h"
#include "file_commands.h"
#include "help_pages.h"
#include "colors.h"
#include "types.h"

int divideLine (char* line, char* command_chunks[])
{
    int i = 0;

    command_chunks[i] = strtok(line, " \n\t");

    while (command_chunks[i] != NULL)                                                        
        command_chunks[++i] = strtok(NULL, " \n\t");

    return i - 1;
}

void processCommand (char* line)
{
    char* command_chunks[MAX_COMMAND_SIZE/2];
    char original[MAX_COMMAND_SIZE];
    strcpy(original, line);

    int paramN = divideLine (line, command_chunks);
    int valid_command = 0;

    if (command_chunks[0] == NULL)
        return;

    if (!strcmp(command_chunks[0], "help")){
        cmd_help(paramN, command_chunks+1);
        valid_command++;
    }
    else if (check_basic_commands(paramN, command_chunks)){
        valid_command++;
    }
    else if (check_history_commands(paramN, command_chunks)){
        valid_command++;
    }
    else if (check_file_commands(paramN, command_chunks)){
        valid_command++;
    }

    if (valid_command) {
        if (strcmp(command_chunks[0], "command"))
            add_history_entry(original);
    }
    else
        printf(RED "Error: " RESET_CLR "not a valid command\n");
}


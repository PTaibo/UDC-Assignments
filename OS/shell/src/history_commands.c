#include "history_commands.h"

#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "colors.h"
#include "list.h"
#include "error_msgs.h"
#include "command_processor.h"
#include "help_pages.h"

basic_list history;

void init_history()
{
    basicList_initialize(&history);
}

void rm_history ()
{
    basicList_clear(&history);
}

struct cmd history_commands[] = {
    {"hist", cmd_hist},
    {"command", cmd_repeat},
    {NULL, NULL}
};

int check_history_commands (int paramN, char* command[])
{
    for (int i = 0; history_commands[i].name != NULL; i++){
        if (!strcmp(command[0], history_commands[i].name)){
            if (!is_help_param(paramN, command))
                (*history_commands[i].funct)(paramN, command+1);
            return 1;
        }
    }

    return 0;
}

void add_history_entry (char* command)
{
    basicList_append(command, &history);
}

void cmd_hist (int paramN, char* command[])
{
    if (!paramN){
        basicList_print(-1, &history);
        return;
    }

    // Print the first n commands from history
    // Checks length to avoid numbers > MAX_INT to be given to atoi
    if (paramN == 1 && strlen(command[0]) < 5 && atoi(command[0]) < 0){
        basicList_print((-1)*atoi(command[0]), &history);
        return;
    }

    if (paramN == 1 && !strcmp(command[0], "-c")){
        basicList_clear(&history);
        return;
    }

    invalid_param();
}

void cmd_repeat (int paramN, char* params[])
{
    if (paramN == 1  && strlen(params[0]) < 5 &&
        // Atoi gives 0 as error and hist starts at 0
       (!strcmp(params[0], "0") || atoi(params[0]) > 0)){
        char command[MAX_COMMAND_SIZE];
        if (basicList_getter(atoi(params[0]), command, &history) != NULL){
            printf(GREEN "%s\n" RESET_CLR, command); // Print command to be executed
            processCommand(command);
            return;
        }
    }

    printf(RED "Error: " RESET_CLR "Invalid parameter\n");
}

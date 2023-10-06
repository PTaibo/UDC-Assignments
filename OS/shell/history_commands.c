#include "history_commands.h"

#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "colors.h"
#include "list.h"
#include "error_msgs.h"
#include "command_processor.h"

List history;

void init_history()
{
    initialize_hist(&history);
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
            (*history_commands[i].funct)(paramN, command+1);
            return 1;
        }
    }

    return 0;
}

void add_history_entry (char* command)
{
    append_element(command, &history);
}

void cmd_hist (int paramN, char* command[])
{
    if (!paramN){
        print_n_elements(-1, &history);
        return;
    }

    if (paramN == 1 && strlen(command[0]) < 5 && atoi(command[0]) < 0){
        print_n_elements((-1)*atoi(command[0]), &history);
        return;
    }

    if (paramN == 1 && !strcmp(command[0], "-c")){
        clear_list(&history);
        return;
    }

    invalid_param();
}

void cmd_repeat (int paramN, char* params[])
{
    // Atoi gives 0 as error and hist starts at 0
    if (paramN == 1  && strlen(params[0]) < 5
        && (!strcmp(params[0], "0") || atoi(params[0]) > 0)){
        char command[MAX_COMMAND_SIZE];
            printf(GREEN "%s" RESET_CLR, command); // Print command to be executed
        get_command(atoi(params[0]), command, &history);
        processCommand(command);
        return;
    }

    printf(RED "Error: " RESET_CLR "Invalid parameter\n");
}


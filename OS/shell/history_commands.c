#include "history_commands.h"

#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "colors.h"
#include "list.h"
#include "utils.h"
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

    if (paramN == 1 && is_number(command[0])){
        print_n_elements(-atoi(command[0]), &history);
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
    if (paramN == 1 && is_number(params[0])){
        char* command = get_command(atoi(params[0]), &history);
        processCommand(command);
        return;
    }

    printf(RED "Error: " RESET_CLR "Invalid parameter\n");
}


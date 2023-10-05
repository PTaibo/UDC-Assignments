#include <stdio.h>
#include <string.h>

#include "types.h"
#include "command_processor.h"

int main()
{
    char line [MAX_COMMAND_SIZE];

    init_file_list();

    init_history();

    printf("> ");

    while (fgets(line, MAX_COMMAND_SIZE, stdin) != NULL){
        processCommand(line);
        printf("> ");
    }

    return 0;
}


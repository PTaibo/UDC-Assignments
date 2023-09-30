#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instructions.h"
#include "valid_commands.h"
#include "list.h"

#define MAXLINE 200

List history;
List opened_files;

int divideLine(char* line, char* instruction [])
{
    int i = 0;

    instruction[i] = strtok(line, " \n\t");

    while (instruction[i] != NULL)
        instruction[++i] = strtok(NULL, " \n\t");

    return i - 1;
}

int find_command(char* instruction[], struct cmd* command_list, int paramN, List* list)
{
    for (int i = 0; command_list[i].name != NULL; i++){
        if (!strcmp(instruction[0], command_list[i].name)){
            (*command_list[i].funct)(paramN, instruction+1, list);
            /* add_element(NULL, instruction[] constructed, history*/ 
            return 1;
        }
    }

    return 0;
}

void executeCommand (int paramN, char* instruction [])
{
    if (instruction[0] == NULL)
        return;

    if (find_command(instruction, valid_commands, paramN, NULL)){
        return;
    }
    if (find_command(instruction, hist_commands, paramN, &history)){
        return;
    }
    if (find_command(instruction, file_commands, paramN, &opened_files)){
        return;
    }

    printf("Command not valid\n");
}

void processCommand (char* line)
{
    char* instruction [MAXLINE/2];

    int paramN = divideLine(line, instruction);
    executeCommand(paramN, instruction);
}

int main()
{
    char line[MAXLINE];

    create_list(&history);
    create_list(&opened_files);

    printf("> ");

    while (fgets(line, MAXLINE, stdin) != NULL){
        processCommand(line);
        printf("> ");
    }

    return 0;
}

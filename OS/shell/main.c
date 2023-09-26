#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instructions.h"
#include "valid_commands.h"

#define MAXLINE 200

int destroyLine(char* line, char* instruction [])
{
    int i = 0;

    instruction[i] = strtok(line, " \n\t");

    while (instruction[i] != NULL)
        instruction[++i] = strtok(NULL, " \n\t");

    return i;
}

void processCommand (int instrucParts, char* instruction [])
{
    if (instruction[0] == NULL)
        return;

    for (int i = 0; valid_commands[i].name != NULL; i++){
        if (!strcmp(instruction[0], valid_commands[i].name)){
            (*valid_commands[i].funct)(instrucParts-1, instruction+1);
            return;
        }
    }

    printf("Command not valid\n");
}

int main()
{
    char line[MAXLINE];
    char* instruction [MAXLINE/2];

    while (1){
        printf("> ");
        fgets(line, MAXLINE, stdin);
        int instrucParts = 0;
        instrucParts = destroyLine(line, instruction);
        processCommand(instrucParts, instruction);
    }

    return 0;
}

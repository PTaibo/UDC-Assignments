#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 200

int dismountLine(char* line, char* instruction [])
{
    int i = 0;

    instruction[i] = strtok(line, " \n\t");

    while (instruction[i] != NULL){
        instruction[++i] = strtok(NULL, " \n\t");

    return i;
}

void Cmd_quit ()
{
    exit(0);
}

void Cmd_authors (int param, char* params[])
{
    // -n parameter
    if (param == 1 && !strcmp(params[0], "-n")
        printf("Siyuan He\nPaula Taibo Suárez");

    // -l parameter
    else if (param == 1 && !strcmp(params[0], "-l")
        printf("siyuan.he\np.taibo\n");

    // Invalid parameters
    else if (param > 2)
        printf("Invalid parameter\n");
    else if (param == 2 && params[0] != "-n" && params[0] != "-l")
        printf("Invalid parameter\n");
    else if (param == 2 && params[1] != "-n" && params[1] != "-l")
        printf("Invalid parameter\n");

    // None or both parameters
    else
        printf("Siyuan He\t\tsiyuan.he\n
                Paula Taibo Suárez\t\tp.taibo\n");
}

void processCommand (int instrucParts, char* instruction [])
{
    if (!strcmp(instruction[0], "quit"))
        Cmd_quit();
    if (!strcmp(instruction[0], "exit"))
        Cmd_quit();
    if (!strcmp(instruction[0], "bye"))
        Cmd_quit();
    if (!strcmp(instruction[0], "authors"))
        Cmd_authors(instrucParts - 1, instruction + 1);

    printf("Command not found\n");
}

int main()
{
    char line[MAXLINE];
    char* instruction [MAXLINE/2];

    while (1){
        printf("> ");
        fgets(line, MAXLINE, stdin);
        int instrucParts = 0;
        instrucParts = dismountLine(line, instruction);
        processCommand(instrucParts, instruction);
    }
}

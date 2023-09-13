#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 200

int dismountLine(char* line, char* command[])
{
    int i = 1;

    command[0] = strtok(line, " \n\t");
    if (command[0] == NULL)
        return 0;
    
    while ((command[i] = strtok(NULL, " \n\t")) != NULL)
        i++;
    return i;
}

void Cmd_quit ()
{
    exit(0);
}

void processCommand (char* command[])
{
    if (!strcmp(command[0], "quit"))
        Cmd_quit();
    if (!strcmp(command[0], "exit"))
        Cmd_quit();
    if (!strcmp(command[0], "bye"))
        Cmd_quit();

    printf("Command not found\n");
}

int main()
{
    char line[MAXLINE];
    char* command[MAXLINE/2];

    while (1){
        printf("> ");
        fgets(line, MAXLINE, stdin);
        dismountLine(line, command);
        processCommand(command);
    }
}

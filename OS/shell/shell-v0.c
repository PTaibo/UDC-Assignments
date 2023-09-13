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



void processCommand (char* command[])
{
}

int main()
{
    char line[MAXLINE];
    char* command[MAXLINE/2];

    while (1){
        printf("> ");
        fgets(line, MAXLINE, stdin);
        int commandSize = 0;
        commandSize = dismountLine(line, command);
        processCommand(commandSize, command);
    }
}

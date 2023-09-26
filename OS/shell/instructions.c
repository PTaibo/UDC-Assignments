#include "instructions.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED __attribute__((unused)) // Gets rid of unused parameter warnings

void cmd_quit(UNUSED int paramN, UNUSED char* params[])
{
    exit(0);
}

void cmd_authors (int paramN, char* params[]){
    const char *name1 = "Siyuan He";
    const char *name2 = "Paula Taibo Suárez";
    const char *login1 = "siyuan.he";
    const char *login2 = "p.taibo";

    // -n parameter
    if (paramN == 1 && !strcmp(params[0], "-n")){
        printf("%s\n%s\n", name1, name2);
    }

    // -l parameter
    else if (paramN == 1 && !strcmp(params[0], "-l"))
        printf("%s\n%s\n", login1, login2);

    // None or both parameters
    else if (!paramN)
        printf("%s\t\t%s\n%s\t%s\n", name1, login1, name2, login2);
    else if (paramN == 2 && (!strcmp(params[0], "-n") || !strcmp(params[0], "-l"))
                && (!strcmp(params[1], "-n") || !strcmp(params[1], "-l")))
        printf("%s\t\t%s\n%s\t%s\n", name1, login1, name2, login2);

    // Invalid or excesive parameters
    else
        printf("Invalid parameter\n");
}

void cmd_pid (int paramN, char* param[])
{
    printf("Gets to pid\n");
    fflush(stdin);
    if (paramN == 1 && !strcmp(param[0], "-p"))
        printf("Shell's parent's pid is %d\n", getppid());
    else if (paramN)
        printf("Invalid parameter\n");
    else
        printf("Shell's pid is%d\n", getpid());
}




#include "instructions.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>

#define RED         "\x1b[31m"
#define GREEN       "\x1b[32m"
#define YELLOW      "\x1b[33m"
#define BLUE        "\x1b[34m"
#define MAGENTA     "\x1b[35m"
#define CYAN        "\x1b[36m"
#define RESET_CLR   "\x1b[0m"

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
        printf(RED "Error: " RESET_CLR "Invalid parameter\n");
}

void cmd_pid (int paramN, char* param[])
{
    if (paramN == 1 && !strcmp(param[0], "-p"))
        printf("Shell's parent's pid is %d\n", getppid());
    else if (paramN)
        printf("Invalid parameter\n");
    else
        printf("Shell's pid is%d\n", getpid());
}

void cmd_chdir (int paramN, char* param[])
{
#define MAX_CWD 1000

    if (paramN > 1){ 
        printf(RED "Error: " RESET_CLR "Invalid parameter\n");
        return;
    }   

    char cwd[MAX_CWD];
    if (!paramN){
        getcwd(cwd, MAX_CWD);
        printf("cwd: %s\n", cwd);
        return;
    }   

    if (!chdir(param[0]))
        return;

    perror(RED "Error: " RESET_CLR "Couldn't change directory");
}

void cmd_infosys (int paramN, UNUSED char* param[])
{
    if (paramN){
        printf(RED "Error: " RESET_CLR "Invalid parameter\n");
        return;
    }

    struct utsname info;
    if (uname(&info) < 0){
        perror("Could not read system info");
        return;
    }

    printf("\n");
    printf(CYAN "Machine: " RESET_CLR "%s\n", info.nodename);
    printf(CYAN "OS: " RESET_CLR "%s\n", info.version);
    printf(CYAN "Kernel: " RESET_CLR "%s %s %s\n", info.sysname,
                                                  info.release,
                                                  info.machine);
#ifdef _GNU_SOURCE 
    printf(CYAN "Domain name:" RESET_CLR "%s\n", info.__domainname);
#endif
    printf("\n");
}


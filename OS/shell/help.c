#include "help.h"
#include <stdio.h>
#include "valid_commands.h"
#include <string.h>

#define RED         "\x1b[31m"
#define GREEN       "\x1b[32m"
#define YELLOW      "\x1b[33m"
#define BLUE        "\x1b[34m"
#define MAGENTA     "\x1b[35m"
#define CYAN        "\x1b[36m"
#define RESET_CLR   "\x1b[0m"
#define CMD_NAME_CLR "\x1b[33m" // Yellow

void cmd_help (int paramN, char* params[])
{
    if (!paramN){
        printf(CMD_NAME_CLR "\nHELP:\n" RESET_CLR
                "\tPrints the help page for a command.\n"
                "\tUsage: help cmd\n\n");
        return;
    }

    if (paramN > 1){
        printf(RED "Error: " RESET_CLR "too many parameters\n");
        return;
    }

    for (int i = 0; help_pages[i].command != NULL; i++){
        if (!strcmp(params[0], help_pages[i].command)){
            printf("\n");
            (*help_pages[i].funct)();
            printf("\n");
            return;
        }
    }
    
    printf(RED "Error: " RESET_CLR "help page not found\n");
}

void help_authors()
{
    printf(CMD_NAME_CLR "\nAUTHORS:\n" RESET_CLR
            "\tPrints the names and logins of the programmers\n"

            "\tUsage: authors [-n] [-l]\n"
            
            "\tParameters:\n"
            "\t\t-n : print only the names\n"
            "\t\t-l : print only the logins\n");
}

void help_pid()
{
    printf(CMD_NAME_CLR "\nPID:\n" RESET_CLR
            "\tPrints the pid of the process executing the shell\n"
            "\tUsage: pid [-p]\n"
            "\tParameters:\n"
            "\t\t-p: prints the pid of the shell's parent process\n");
}

void help_chdir()
{
    printf(CMD_NAME_CLR "\nCHDIR:\n" RESET_CLR
            "\tPrints the current working directory of the shell\n"
            "\tUsage: chdir [dir]\n"
            "\tOptions:\n"
            "\t\tdir: change the current working directory to the one specified\n");
}

void help_infosys()
{
    printf(CMD_NAME_CLR "\nINFOSYS:\N" RESET_CLR
            "\tPrints the information of the machine that's running the shell\n"
            "\tUsage: infosys\n"
}


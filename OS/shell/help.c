#include "instructions.h"
#include <stdio.h>

#define RED         "\x1b[31m"
#define GREEN       "\x1b[32m"
#define YELLOW      "\x1b[33m"
#define BLUE        "\x1b[34m"
#define MAGENTA     "\x1b[35m"
#define CYAN        "\x1b[36m"
#define RESET_CLR   "\x1b[0m"

void cmd_help (int paramN, char* params[])
{
    if (!paramN){
        printf(YELLOW "\nHELP:\n" RESET_CLR
                "\tPrints the help page for a command.\n"
                "\tUsage: help cmd\n\n");
        return;
    }
    
    printf(RED "Error: " RESET_CLR "command doesn't exist\n");
}

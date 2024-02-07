/*
 * Name: Siyuan He              Login: siyuan.he
 * Name: Paula Taibo Suárez     Login: p.taibo
 */

#include "external_commands.h"

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

#include "colors.h"
#include "process_commands.h"
#include "basic_commands.h"

void print_error()
{
    perror(RED "Error: " RESET_CLR
           "Could not execute external command");
}

pid_t create_child (char* command[])
{
    pid_t child = fork();

    if (child == 0) {
        if (execvp(command[0], command) == -1) {
            print_error();
            cmd_quit(0, NULL);
        }
    }

    if (child < 0){
        print_error();
        return -1;
    }

    return child;
}



void execute_external_command(int arguments, char* command[])
{
    int background_process = 0;
    if (arguments > 1 && !strcmp(command[arguments-1], "&")) {
        background_process = 1;
        command[arguments-1] = NULL;
    }

    pid_t child = create_child (command);

    if (child == -1) return;
    if (!background_process)
        waitpid(child, NULL, 0);
    else
        new_process(command[0], child);

   return;
}

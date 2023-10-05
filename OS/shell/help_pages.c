#include "help_pages.h"

#include <stdio.h>
#include <string.h>

#include "colors.h"
#include "error_msgs.h"

#define CMD_NAME_CLR "\x1b[33m" // Yellow

struct help {
    char* command;
    void (*funct)();
};

struct help help_page[] = {
  {"-l", list_commands},
  {"help", help_help},
  {"authors", help_authors},
  {"pid", help_pid},
  {"chdir", help_chdir},
  {"date", help_date},
  {"time", help_time},
  {"hist", help_hist},
  {"command", help_command},
  {"open", help_open},
  {"close", help_close},
  {"dup", help_dup},
  {"listopen", help_listopen},
  {"infosys", help_infosys},
  {"quit", help_quit},
  {"exit", help_quit},
  {"bye", help_quit},
  {NULL, NULL}
}; 

void cmd_help (int paramN, char* params[])
{
    if (!paramN){
        (*help_page[1].funct)();
        return;
    }
    if (paramN > 1){
        invalid_param();
        return;
    }

    for (int i = 0; help_page[i].command != NULL; i++){
        if (!strcmp(params[0], help_page[i].command)){
            (*help_page[i].funct)();
            printf("\n");
            return;
        }
    }

    printf(RED "Error: " RESET_CLR "help page not found\n");
}

void help_help()
{
    printf(CMD_NAME_CLR "\nHELP:\n" RESET_CLR
                  "\tPrints the help page for a command.\n"
                  "\tUsage: help [cmd|-l]\n"
                  "\tOptions:\n"
                  "\t\tcmd: prints the help page of the command\n"
                  "\t\t-l: lists all the avaliable commands\n\n");
}

void list_commands()
{
    printf("\nThe avaliable commands are:\n");
        for (int i = 1; help_page[i].command != NULL; i++){
            printf("\t%s\n", help_page[i].command);
        }
        return;
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
    printf(CMD_NAME_CLR "\nINFOSYS:\n" RESET_CLR
            "\tPrints the information of the machine that's running the shell\n"
            "\tUsage: infosys\n");
}

void help_quit()
{
    printf(CMD_NAME_CLR "\nQUIT/EXIT/BYE:\n" RESET_CLR
            "\tExits the shell\n"
            "\tUsage: quit/exit/bye\n");
}

void help_date()
{
    printf(CMD_NAME_CLR "\nDATE:\n" RESET_CLR
            "\tPrints the current date\n"
            "\tUsage: date\n"
            "\tFormat: DD/MM/YYYY\n");
}

void help_time()
{
    printf(CMD_NAME_CLR "\nTIME:\n" RESET_CLR
            "\tPrints the current time\n"
            "\tUsage: time\n"
            "\tFormat: hh:mm:ss\n");
}

void help_hist()
{
    printf(CMD_NAME_CLR "\nHIST:\n" RESET_CLR
            "\tShows the historic of commands executed "
            "by the shell and their order number\n"
            "\tUsage: hist [-c | -N]\n"
            "\tParameters:\n"
            "\t\t-c: clears the historic\n"
            "\t\t-N: prints the first N commands\n");
}

void help_command()
{
    printf(CMD_NAME_CLR "\nCOMMAND:\n" RESET_CLR
            "\tRepeats command number N of the historic\n"
            "\tUsage: command N\n");
}

void help_open()
{
    printf(CMD_NAME_CLR "\nOPEN:\n" RESET_CLR
            "\tOpens a specified file\n"
            "\tUsage: open [file] [mode]\n"
            "\tOptions:\n"
            "\t\tfile: file to open\n"
            "\t\tmode: opening mode\n"
            "\tOpening modes:\n"
            "\t\tcr: create the file. If it already exists it opens it\n"
            "\t\tap: append information to an existing file\n"
            "\t\tex: used with cr. Forces the file to be opened.\n"
            "\t\t    Returns error if file already exists\n"
            "\t\tro: read only mode\n"
            "\t\trw: read write mode\n"
            "\t\two: write only mode\n"
            "\t\ttr: truncates the file (length 0)\n");
}

void help_close()
{
    printf(CMD_NAME_CLR "\nCLOSE:\n" RESET_CLR
            "\tCloses a specified file\n"
            "\tUsage: cloase [fd]\n"
            "\tOptions:\n"
            "\t\tfd: file descriptor of the opened file\n"
            "\tRelated commands: listopen (gives you the list of opened\n"
            "\t\t\t  files with their file descriptors\n");
}

void help_dup()
{
    printf(CMD_NAME_CLR "\nDUP:\n" RESET_CLR
            "\tDuplicates a specified file descriptor\n"
            "\tUsage: dup [fd]\n"
            "\tOptions:\n"
            "\t\tfd: file descriptor to duplicate\n"
            "\tRelated commands: listopen (gives you the list of opened\n"
            "\t\t\t  files with their file descriptors\n");
}

void help_listopen()
{
    printf(CMD_NAME_CLR "\nLISTOPEN:\n" RESET_CLR
            "\tLists the shells's opened files\n"
            "\tFormat: file descriptor, name, opening mode\n");
}



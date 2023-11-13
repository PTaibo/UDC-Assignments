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
  {"create", help_create},
  {"stat", help_stat},
  {"list", help_list},
  {"delete", help_delete},
  {"deltree", help_deltree},
  {NULL, NULL}
}; 

void find_help_page (char* command)
{
    for (int i = 0; help_page[i].command != NULL; i++){
        if (!strcmp(command, help_page[i].command)){
            (*help_page[i].funct)();
            printf("\n");
            return;
        }
    }
}

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

    find_help_page(params[0]);

    printf(RED "Error: " RESET_CLR "help page not found\n");
}

int is_help_param (int paramN, char* command[])
{
    if (paramN > 0 && (!strcmp(command[1], "-?") ||
                !strcmp(command[1], "-help"))){
        find_help_page(command[0]);
        return 1;
    }
    return 0;
}

void help_help()
{
    printf(CMD_NAME_CLR "\nHELP:\n" RESET_CLR
                  "\tPrints the help page for a command.\n"
                  "\tUsage: help [cmd|-l]\n"
                  "\tOptions:\n"
                  "\t\tcmd: prints the help page of the command\n"
                  "\t\t-l: lists all the avaliable commands\n\n"
                  "\tIt is also possible to use \"<command> -?/-help\"\n");
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
            "\tUsage: close [fd]\n"
            "\tOptions:\n"
            "\t\tfd: file descriptor of the opened file\n"
            "\tRelated commands: listopen (gives you the list of opened\n"
            "\t\t\t  files with their file descriptors)\n");
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

void help_create()
{
    printf(CMD_NAME_CLR "\nCREATE:\n" RESET_CLR
            "\tCreates files or directories\n"
            "\tUsage: create [-f] [name]\n"
            "\tParameters:\n"
            "\t\t-f: creates a file instead of a directory\n");
}

void help_stat()
{
    printf(CMD_NAME_CLR "\nSTAT:\n" RESET_CLR
            "\tGives information on files or directories\n"
            "\tUsage: stat [-long][-link][-acc] name1 name2..\n"
            "\tParameters:\n"
            "\t\t-long: long listing\n"
            "\t\t-acc: accesstime\n"
            "\t\t-link: prints contained path of symbolic links\n");
}

void help_list()
{
    printf(CMD_NAME_CLR "\nLIST:\n" RESET_CLR
            "\tLists directory contents\n"
            "\tUsage: list [-reca][-recb][-hid][-long][-link][-acc] [DIRS]\n"
            "\tParameters:\n"
            "\t\t-reca: recursive (after)\n"
            "\t\t-recb: recursive (before)\n"
            "\t\t-hid: includes hidden files\n"
            "\t\t-long: long listing\n"
            "\t\t-link: prints contained path of symbolic links\n"
            "\t\t-acc: accesstime\n");
}

void help_delete()
{
    printf(CMD_NAME_CLR "\nDELETE:\n" RESET_CLR
            "\tDeletes files and/or emtpy directories\n"
            "\tUsage: delete [NAMES]\n");
}

void help_deltree()
{
    printf(CMD_NAME_CLR "\nDELTREE:\n" RESET_CLR
            "\tDeletes files and/or empty directories recursively\n"
            "\tUsage: deltree [NAMES]\n");
}


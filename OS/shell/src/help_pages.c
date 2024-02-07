/*
 * Name: Siyuan He              Login: siyuan.he
 * Name: Paula Taibo Suárez     Login: p.taibo
 */

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
    {"malloc", help_malloc},
    {"shared", help_shared},
    {"mmap", help_mmap},
    {"read", help_read},
    {"write", help_write},
    {"memdump", help_memdump},
    {"memfill", help_memfill},
    {"mem", help_mem},
    {"recurse", help_recurse},
    {"uid", help_uid},
    {"showvar", help_showvar},
    {"changevar", help_changevar},
    {"subsvar", help_subsvar},
    {"showenv", help_showenv},
    {"fork", help_fork},
    {"exec", help_exec},
    {"jobs", help_jobs},
    {"deljobs", help_deljobs},
    {"job", help_job},
    {NULL, NULL}
}; 

int find_help_page (char* command)
{
    for (int i = 0; help_page[i].command != NULL; i++){
        if (!strcmp(command, help_page[i].command)){
            (*help_page[i].funct)();
            printf("\n");
            return 1;
        }
    }
    return 0;
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

    if (!find_help_page(params[0]))
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
    printf("You can also execute some external commands\n"
           "(ls, cal...)\nAdd & to the end to execute in the background");
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

void help_malloc()
{
    printf(CMD_NAME_CLR "\nMALLOC:\n" RESET_CLR
            "\tLists the allocated blocks for the shell\n"
            "\tUsage: malloc [-free] [size]\n"
            "\tParameters:\n"
            "\t\tsize: allocates a block of the specified size\n"
            "\t\t-free: frees a block of the specified size\n");
}

void help_shared()
{
    printf(CMD_NAME_CLR "\nSHARED:\n" RESET_CLR
            "\tLists the assigned shared blocks for the shell\n"
            "\tUsage: shared [-free|-create|-delkey key [size]]\n"
            "\tParameters:\n"
            "\t\tkey: assign shared memory to process\n"
            "\t\t-free key: unmaps the specified shared memory block\n"
            "\t\t-create key size: creates a shared memory block of the\n"
            "\t\t                  specified size and assignes the specified key\n"
            "\t\t-delkey key: eliminates the specified key (no the memory block)\n");
}

void help_mmap()
{
    printf(CMD_NAME_CLR "\nMMAP:\n" RESET_CLR
            "\tLists the mmap assigned blocks for the shell\n"
            "\tUsage: mmap [-free] file [mode]\n"
            "\tParameters:\n"
            "\t\tmode: maps the file with the specified permissions\n"
            "\t\t-free: unmaps the file\n");
}

void help_read()
{
    printf(CMD_NAME_CLR "\nREAD:\n" RESET_CLR
            "\tReads a number of bytes from a file to an address\n"
            "\tUsage: read file addr bytes\n");
}

void help_write()
{
    printf(CMD_NAME_CLR "\nWRITE:\n" RESET_CLR
            "\tWrites a number of bytes from an address to a file\n"
            "\tUsage: [-o] file addr bytes\n"
            "\tParameters:\n"
            "\t\t-o: overwrite the file\n");
}

void help_memdump()
{
    printf(CMD_NAME_CLR "\nMEMDUMP:\n" RESET_CLR
            "\tDumps to screen the contents of a memory address\n"
            "\tUsage: memdump addr [bytes]\n"
            "\tIf stated, it dumps a specified number of bytes\n");
}

void help_memfill()
{
    printf(CMD_NAME_CLR "\nMEMFILL:\n" RESET_CLR
            "\tFills n bytes of a block of memory with a specified character\n"
            "\tUsage: memfill addr n char\n");
}

void help_mem()
{
    printf(CMD_NAME_CLR "\nMEM:\n" RESET_CLR
            "\tPrints the details of the process' memory\n"
            "\tUsage: mem [-blocks | -funcs | -vars | -all | -pmap]\n"
            "\tParameters:\n"
            "\t\t-blocks: assigned memory blocks\n"
            "\t\t-funcs: function addresses\n"
            "\t\t-vars: variable addresses\n"
            "\t\t-all: all of the above. Same as no params\n"
            "\t\t-pmap: shows the output of the pmap command (or similar)\n");
}

void help_recurse()
{
    printf(CMD_NAME_CLR "\nRECURSE\n" RESET_CLR
            "\tExecutes a recursive function n times\n"
            "\tUsage: recurse n\n");
}

void help_uid()
{
    printf(CMD_NAME_CLR "\nUID\n" RESET_CLR
           "\tView the process's credentials\n"
           "\tUsage: uid [-get|-set] [-l][id]\n"
           "\tParameters:\n"
           "\t\t-get: prints the credentials (same as no parameters)\n"
           "\t\t-set id: sets the credentials to that id\n"
           "\t\t-set -l id: sets the credentiasl to a login id\n");
}

void help_showvar()
{
    printf(CMD_NAME_CLR "\nSHOWVAR\n" RESET_CLR
           "\tShows the value and address of the enviroment variable\n"
           "\tUsage: showvar var\n");
}

void help_changevar()
{
    printf(CMD_NAME_CLR "\nCHANGEVAR\n" RESET_CLR
           "\tChanges the value of an enviroment variable\n"
           "\tUsage: changevar [-a|-e|-p] var value\n"
           "\tParameters:\n"
           "\t\t-a: accesses using the third argument of main\n"
           "\t\t-e: accesses using environ\n"
           "\t\t-p: accesses using putenv\n");
}

void help_subsvar()
{
    printf(CMD_NAME_CLR "\nSUBSVAR\n" RESET_CLR
           "\tChanges one enviroment variable for other\n"
           "\tUsage: subsvar [-a|-e] varold varnew value\n"
           "\tParameters:\n"
           "\t\t-a: accesses using the third argument of main\n"
           "\t\t-e: accesses using environ\n");
}

void help_showenv()
{
    printf(CMD_NAME_CLR "\nSHOWENV\n" RESET_CLR
           "\tShows the process enviroment.\n"
           "\tAccesses using the third argument of main\n"
           "\tUsage: showenv [-environ|-addr]\n"
           "\tParameters:\n"
           "\t\t-environ: accesses using environ\n"
           "\t\t-addr: shows the value and storage address\n"
           "\t\t       of environ and the third argument of main\n");
}

void help_fork()
{
    printf(CMD_NAME_CLR "\nFORK\n" RESET_CLR
           "\tThe shell does the fork system call\n"
           "\tand waits for its child to end\n"
           "\tUsage: fork\n");
}

void help_exec()
{
    printf(CMD_NAME_CLR "\nFORK\n" RESET_CLR
           "\tExecutes a program with arguments\n"
           "\twithout creating a new process\n"
           "\tUsage: exec program arguments\n");
}

void help_jobs()
{
    printf(CMD_NAME_CLR "\nJOBS\n" RESET_CLR
           "\tLists background processes\n"
           "\tUsage: jobs\n");
}

void help_deljobs()
{
    printf(CMD_NAME_CLR "\nDELJOBS\n" RESET_CLR
           "\tDeletes background processes from the list\n"
           "\tUsage: deljobs [-term][-sig]\n"
           "\tParameters:\n"
           "\t\t-term: terminated processes\n"
           "\t\t-sig: terminated by signal\n");
}

void help_job()
{
    printf(CMD_NAME_CLR "\nJOB\n" RESET_CLR
           "\tShows info on a background process\n"
           "\tUsage: job [-fg] pid\n"
           "\tParameters:\n"
           "\t\t-fg: changes it to foreground\n");
}


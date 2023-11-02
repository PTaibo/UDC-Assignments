#include "basic_commands.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <time.h>

#include "types.h"
#include "colors.h"
#include "error_msgs.h"
#include "file_commands.h"
#include "history_commands.h"
#include "help_pages.h"

struct cmd command_list[] = {
    {"authors", cmd_authors},
    {"pid", cmd_pid},
    {"chdir", cmd_chdir},
    {"date", cmd_date},
    {"time", cmd_time},
    {"infosys", cmd_infosys},
    {"quit", cmd_quit},
    {"exit", cmd_quit},
    {"bye", cmd_quit},
    {NULL, NULL}
};

int check_basic_commands (int paramN, char* command[])
{
    for (int i = 0; command_list[i].name != NULL; i++){
        if (!strcmp(command[0], command_list[i].name)){
            if (!is_help_param(paramN, command))
                (*command_list[i].funct)(paramN, command+1);
            return 1;
        }
    }
    
    return 0;
}

void cmd_quit(UNUSED int paramN, UNUSED char* params[])
{
    rm_file_list();
    rm_history();
    
    exit(0);
}

void print_names ()
{
    printf("Siyuan He\tPaula Taibo Suárez\n");
}

void print_logins ()
{
    printf("siyuan.he\tp.taibo\n");
}

void cmd_authors (int paramN, char* params[]){
    // -n parameter
    if (paramN == 1 && !strcmp(params[0], "-n")){
        print_names();
    }
    // -l parameter
    else if (paramN == 1 && !strcmp(params[0], "-l")){
        print_logins();
    }
    // None or both parameters
    else if (!paramN){
        print_names();
        print_logins();
    }
    else if (paramN == 2 && (!strcmp(params[0], "-n") || !strcmp(params[0], "-l"))
                && (!strcmp(params[1], "-n") || !strcmp(params[1], "-l"))){
        print_names();
        print_logins();
    }
    // Invalid parameters (rest of cases)
    else
        invalid_param();
}

void cmd_pid (int paramN, char* param[])
{
    if (paramN == 1 && !strcmp(param[0], "-p"))
        printf("Shell's parent's pid is %d\n", getppid());

    else if (paramN)
        invalid_param();

    else
        printf("Shell's pid is %d\n", getpid());
}

void cmd_time (int paramN, UNUSED char* params[])
{
    if(paramN!=0){
        invalid_param();
    }
    else {
        char tiempo[9];
        time_t result = time(NULL);
        strftime( tiempo, 9, "%T", localtime(&result));
        printf("%s\n", tiempo);
    }
}

void cmd_date (int paramN, UNUSED char* params[])
{
    if(paramN!=0){
        invalid_param();
    }
    else {
        char tiempo[12];
        time_t result = time(NULL);
        strftime( tiempo, 12, "%d/%m/%Y", localtime(&result));
        printf("%s\n", tiempo);
    }
}

void cmd_chdir (int paramN, char* param[])
{
    const int MAX_CWD = 1000;

    if (paramN > 1){
        invalid_param();
        return;
    }

    if (paramN == 1 && chdir(param[0])){
        perror(RED "Error: " RESET_CLR "Couldn't change directory");
    }

    char cwd[MAX_CWD];
    getcwd(cwd, MAX_CWD);
    printf("%s\n", cwd);
}

void cmd_infosys (int paramN, UNUSED char* param[])
{
    if (paramN){
        invalid_param();
        return;
    }

    struct utsname info;
    if (uname(&info) < 0){
        perror("Could not read system info");
        return;
    }

    printf("\n");
    printf(CYAN "Machine: " RESET_CLR "%s (%s)\n", info.nodename,
                                                   info.machine);
    printf(CYAN "OS: " RESET_CLR "%s\n", info.version);
    printf(CYAN "Kernel: " RESET_CLR "%s %s\n", info.sysname,
                                                  info.release);
#ifdef _GNU_SOURCE
    printf(CYAN "Domain name:" RESET_CLR "%s\n", info.__domainname);
#endif
    printf("\n");
}


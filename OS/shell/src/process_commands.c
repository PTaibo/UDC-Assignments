#include "process_commands.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <errno.h>

#include "types.h"
#include "list.h"
#include "help_pages.h"
#include "colors.h"
#include "error_msgs.h"
#include "env.h"

/* DynamicList procList; */

/* void init_proc() */
/* { */
/*     dynList_init(&procList); */
/* } */

/* void delete_procblock() */
/* { */
/* } */

/* void rm_proc() */
/* { */
/*     dynList_clear(delete_procblock, &procList); */
/* } */

struct cmd proc_commands[] = {
    {"uid", cmd_uid},
    {"showvar", cmd_showvar},
    // {"changevar", cmd_changevar},
    // {"subsvar", cmd_subsvar}, 
    {"showenv", cmd_showenv},
    // {"fork", cmd_fork}, 
    // {"exec", cmd_exec}, 
    /* {"jobs", cmd_jobs}, */
    /* {"deljobs", cmd_deljobs}, */
    /* {"job", cmd_job}, */
    {NULL, NULL}
};

int check_process_commands (int paramN, char* command[])
{
    for (int i = 0; proc_commands[i].name != NULL; i++){
        if (!strcmp(command[0], proc_commands[i].name)){
            if (!is_help_param(paramN, command))
                (*proc_commands[i].funct)(paramN, command+1);
            return 1;
        } 
    }

    return 0;
}

void dysplayUID(){
    uid_t uid = getuid();
    uid_t euid = geteuid();

    struct passwd *u = getpwuid(uid);
    struct passwd *e = getpwuid (euid);

    if (u == NULL){
        perror("No user");
    }
    else printf("Real credential: %d User:%s\n",uid, e->pw_name);

    if (e == NULL){
        perror("No user");
    }
    else printf("Effective credential: %d User:%s\n",euid, e->pw_name);
}

void changeUID(char* command, int type){
    uid_t uid = (uid_t) atoi(command);
    
    if (!type){
        if (setuid(uid) == -1){
            printf(RED "Error: " RESET_CLR "cannot change credential\n");
        }
        else dysplayUID();
    }
    else {
        struct passwd *p;
        if ( (p = getpwnam(command)) == NULL){
           printf(RED "Error: " RESET_CLR "No user %s\n",command);
           return;
        }
        if (setuid(p->pw_uid) == -1){
            printf(RED "Error: " RESET_CLR "cannot change credential\n");
            return;
        }
        else dysplayUID();
    }
    return;
}

void cmd_uid(int paramN, char* command[])
{
    //uid [-get|-set] [-l] [id] no get
    if (!paramN)
        dysplayUID();
    else if (paramN > 0){

        if (paramN == 1 && !strcmp(command[0],"-get")){
            dysplayUID();
            return;
        }

        else if (!strcmp(command[0],"-set")){
            if ((paramN == 2) && (strcmp(command[1],"-l"))){
                changeUID(command[1], 0);
                return;
            }
            if (paramN == 3){
                if (!strcmp(command[1],"-l")){
                    changeUID(command[2], 1);
                    return;
                }
            }
        }

        invalid_param();
    }
    else invalid_param();
    return;
}

void showenv(char **enviroment, char* enviromentname)
{
    int argc = (int) get_args();
    if (argc){
        char** argv = get_argv();
        for (int i = 0; i < argc; i++)
        printf ("%p->argv[%d]=(%p) %s\n", &argv[i], i, argv[i], argv[i]);
    }

    for (int i = 0; enviroment[i] != NULL; i++){
        printf("%p->%s[%d]=(%p) %s\n",&enviroment[i],
                                      enviromentname,
                                      i,
                                      enviroment[i],
                                      enviroment[i]);
    }
}

int postionvar(char **env, char* var)
{
    int p = -1;
    for (int i = 0; env[i] != NULL; i++){
        int lengthvar = strlen(var);
        if (!strncmp(env[i],var,lengthvar) && env[i][lengthvar] == '='){
            p = i;
            continue;
        }
    }    
    return p;
}

void printvar(int p, char* var, char **env)
{
    if (p == -1){
        //errno=ENOENT;
        printf(RED "Error: " RESET_CLR "cannot find variable %s\n", var);
        //perror(RED "Error: " RESET_CLR "cannot find
    } 
    else{
        char** marg = get_mainarg3();
        printf(CYAN "Con main arg3 = " RESET_CLR"%s(%p) @%p\n", marg[p], marg[p], &marg[p]);
        printf(CYAN "Con environ = " RESET_CLR"%s(%p) @%p\n", env[p], env[p], &env[p]);
        printf(CYAN "Con getenv = " RESET_CLR "%s (%p)\n", getenv(var), getenv(var));
    }
}

void cmd_showvar(int paramN, char* command[]) 
{ 
    if (!paramN){
        //showvar
        showenv(get_mainarg3(),"main arg3");
    }
    
    else if (paramN == 1){
        //showvar <var>
        int pos = 0;
        pos = postionvar(get_mainarg3(),command[0]);
        printvar(pos, command[0], __environ);
    }

    else invalid_param();
} 

int changevar (char** env, char* var, char* valor)
{                                                   
  int pos;
  char *aux;
   
  if ((pos=postionvar(env, var)) == -1)
    return(-1);
 
  if ((aux=(char *)malloc(strlen(var)+strlen(valor)+2)) == NULL)//for the = and the \0
	return -1;

  strcpy(aux,var);
  strcat(aux,"=");
  strcat(aux,valor);

  env[pos]=aux;
  return (pos);
}

void cmd_changevar(int paramN, char* command[])
{
    //changevar [-a| -e | -p] var valor
    if (paramN < 3){
        missing_param();
    }
    
    else if (paramN == 3){
    
        if (strcmp(command[0],"-a")){
            int p = 0;
            p = changevar(get_mainarg3(), command[1], command[2]);
            printvar(p, command[1],get_mainarg3());
        }
        else if (strcmp(command[0], "-e")){
            int p = 0;
            p = changevar(__environ, command[1], command[2]);
            printvar(p, command[1], __environ);
        }

        else if (strcmp(command[0], "-p")){
            int p = 0;
            p = changevar(__environ, command[1], command[2]);
            printvar(p, command[1], __environ);
        }

        else invalid_param(); 
        

    } 

    else invalid_param();
}

/* void cmd_subsvar(int paramN, char **command) */
/* { */
/* } */


void cmd_showenv (int paramN, char* command[])
{
    if(!paramN){
        //showenv
        showenv(get_mainarg3(),"main arg3");
    }

    else if (paramN == 1){
        //showenv -environ
        if (!strcmp(command[0],"-environ")){
            showenv(__environ,"environ");
        }
        //showenv -addr 
        else if (!strcmp(command[0],"-addr")){
            char** mainarg = get_mainarg3();
            printf(CYAN"environ: " RESET_CLR"%p (keep in %p)\n", __environ, &__environ);
            printf(CYAN"main arg3: "RESET_CLR"%p (keep in %p)\n", mainarg, &mainarg);
        }
        else invalid_param();
    }

    else invalid_param();
}

/* void cmd_fork(int paramN, char **command) */
/* { */
/* } */

/* void cmd_exec(int paramN, char **command) */
/* { */
/* } */

/* void cmd_jobs(int paramN, char **command) */
/* { */
/* } */

/* void cmd_deljobs(int paramN, char **command) */
/* { */
/* } */

/* void cmd_job(int paramN, char **command) */
/* { */
/* } */


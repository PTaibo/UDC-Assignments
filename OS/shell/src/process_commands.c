#include "process_commands.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <errno.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/types.h>

#include "types.h"
#include "list.h"
#include "help_pages.h"
#include "colors.h"
#include "error_msgs.h"
#include "proc_signals.h"
#include "env.h"
#include "mem_commands.h"

DynamicList procList;
DynamicList env_vars;

void init_proc()
{
    dynList_init(&procList);
}

void init_env_vars()
{
    dynList_init(&env_vars);
}

void delete_procblock(void* p)
{
    process *proc = (process*) p;
    free(proc->name);
    free(proc->launch_time);
}

void rm_proc()
{
    dynList_clear(delete_procblock, &procList);
}

void rm_env_var()
{
    dynList_clear(NULL, &env_vars);
}

struct cmd proc_commands[] = {
    {"uid", cmd_uid},
    {"showvar", cmd_showvar},
    {"changevar", cmd_changevar},
    {"subsvar", cmd_subsvar}, 
    {"showenv", cmd_showenv},
    {"fork", cmd_fork},
    /* {"exec", cmd_exec}, */
    {"jobs", cmd_jobs},
    /* {"deljobs", cmd_deljobs}, */
    {"job", cmd_job},
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
    else printf(CYAN "Real credential: "RESET_CLR "%d User:%s\n",uid, e->pw_name);

    if (e == NULL){
        perror("No user");
    }
    else printf(CYAN "Effective credential: "RESET_CLR"%d User:%s\n",euid, e->pw_name);
}

void changeUID(char* command, int type){
    uid_t uid = (uid_t) atoi(command);
    
    if (!type){
        if (seteuid(uid) == -1){
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
        if (seteuid(p->pw_uid) == -1){
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
        printf(CYAN "With main arg3 = " RESET_CLR"%s(%p) @%p\n", marg[p], marg[p], &marg[p]);
        printf(CYAN "With environ = " RESET_CLR"%s(%p) @%p\n", env[p], env[p], &env[p]);
        printf(CYAN "With getenv = " RESET_CLR "%s (%p)\n", getenv(var), getenv(var));
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
        pos = postionvar(__environ,command[0]);
        printvar(pos, command[0], __environ);
    }

    else invalid_param();
} 

int changevar (char** env, char* var, char* value, int swtch)
{   
    int pos = 0;
    char *aux = NULL;

    if (!swtch){
        if ((pos=postionvar(env, var)) == -1)
            return (pos);

        if ((aux=(char *)malloc(strlen(var)+strlen(value)+2)) == NULL)//for the = and the \0
            return (-1);

        strcpy(aux,var);
        strcat(aux,"=");
        strcat(aux,value);

        env[pos]=aux;
        dynList_add(aux, &env_vars);
        return (pos);
    }
    else {
        aux=malloc(strlen(var)+strlen(value)+2);
        strcpy(aux,var);
        strcat(aux,"=");
        strcat(aux,value);
        putenv(aux);
        dynList_add(aux, &env_vars);
        pos = postionvar(__environ, var);
        return pos;
    }
}


void cmd_changevar(int paramN, char* command[])
{
    //changevar [-a| -e | -p] var valor
    if (paramN < 3){
        missing_param();
    }
    
    else if (paramN == 3){
    
        if (!strcmp(command[0],"-a")){
            int p = 0;
            p = changevar(get_mainarg3(), command[1], command[2], 0);
            printvar(p, command[1],get_mainarg3());
        }
        else if (!strcmp(command[0], "-e")){
            int p = 0;
            p = changevar(__environ, command[1], command[2], 0);
            printvar(p, command[1], __environ);
        }

        else if (!strcmp(command[0], "-p")){
            int p = 0;
            p = changevar(__environ, command[1], command[2], 1);
            printvar(p, command[1], __environ);
        }

        else invalid_param();  
    } 

    else invalid_param();
}

void subsvar(char** env, char* var1, char* var2, char* value)
{
    int pos1 = 0, pos2 = 0;
    pos1 = postionvar(env, var1);
    pos2 = postionvar(env, var2);

    if (pos1 == -1 || pos2 != -1){
        printf(RED "Error: " RESET_CLR "cannot substitue variable %s to %s",var1, var2);
    }

    char* aux = NULL;
    aux = (char *)malloc(strlen(var2)+strlen(value)+2);//for the = and the \0

    strcpy(aux,var2);
    strcat(aux,"=");
    strcat(aux,value);

    env[pos1]=aux;
    dynList_add(aux, &env_vars);
}

void cmd_subsvar(int paramN, char* command[])
{ 
    //subsvar [-a | -e] var1 var2 value
    if (paramN == 4){

        if(!strcmp(command[0],"-a")){
            subsvar(get_mainarg3(),command[1], command[2], command[3]);
        }

        else if(!strcmp(command[0],"-e")){
            subsvar(__environ,command[1], command[2], command[3]);
        }

        else invalid_param();

    } 
    else invalid_param();
} 


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

void cmd_fork(int paramN, UNUSED char* command[]) 
{ 
    if (paramN == 0){
    pid_t pid;
	
	if ((pid=fork())==0){
/*		VaciarListaProcesos(&LP); Depende de la implementación de cada uno*/
		printf ("ejecutando proceso %d\n", getpid());
	}
	else if (pid!=-1)
		waitpid (pid,NULL,0);
    }
    else invalid_param();
}

/* void cmd_exec(int paramN, char* command[]) */
/* { */
/* } */

void new_process (char* name, pid_t pid)
{
    process *proc = malloc(sizeof(process));
    proc->pid = pid;
    proc->status = proc_status[0].value;
    proc->name = malloc(MAX_ELEMENTS);
    strcpy(proc->name, name);
    proc->launch_time = parse_time();
    dynList_add(proc, &procList);
}

int update_proc_info (process *proc)
{
    // TODO
    // waitpid reports status changes (not the state itself)
    // wstats has only a meaningful value if waitpid returns the pid
    // Priority is checked here. Return it.
    return getpriority(PRIO_PROCESS, proc->pid);
}

void print_proc_info (process *proc)
{
    int priority = update_proc_info(proc);
    printf("%d  p:%d  %s ", proc->pid,
                        priority,
                        proc-> launch_time);
    for (int i = 0; proc_status[i].value != -1; i++) {
        if (proc->status == proc_status[i].value){
            printf(" %s ", proc_status[i].name);
            break;
        }
    }
    printf(" %s ", proc->name);
    printf("\n");
}

void cmd_jobs(UNUSED int paramN, UNUSED char **command)
{
    Pos pos = dynList_first(procList);
    for (; pos != NULL; pos = dynList_next(&pos)){
        process *proc = dynList_getter(pos);
        print_proc_info(proc);
    }
}

void cmd_deljobs(int paramN, char* command[])
{
    
}

process* find_job_by_pid (int pid){
    Pos pos = dynList_first(procList);
    for (; pos != NULL; pos = dynList_next(&pos)) {
        process *proc = dynList_getter(pos);
        if (proc->pid == pid) {
            return proc;
        }
    }   
    return NULL;
}

void delete_process (int pid)
{
    Pos pos = dynList_first(procList);
    for (; pos != NULL; pos = dynList_next(&pos)) {
        process *proc = dynList_getter(pos);
        if (proc->pid == pid) {
            dynList_delete(delete_procblock, pos, &procList);
            return;
        }
    }
}

void move_to_foreground (int pid)
{
    // tcsetpgrp(fd, pid);
    delete_process(pid);
}

void cmd_job(int paramN, char* command[])
{
    if (!paramN)
        return missing_param();
    if (paramN == 1 && atoi(command[0])) {
        process *proc = find_job_by_pid(atoi(command[0]));
        if (proc == NULL)
            printf(RED "Error: " RESET_CLR "pid not in list\n");
        else
            print_proc_info(proc);
    }
    if (paramN == 2 && !strcmp(command[0], "-fg"))
        move_to_foreground(atoi(command[1]));
}

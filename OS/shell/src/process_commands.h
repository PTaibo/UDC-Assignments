/*
 * Name: Siyuan He              Login: siyuan.he
 * Name: Paula Taibo Suárez     Login: p.taibo
 */

#pragma once

#include <unistd.h>
#include "types.h"

void init_proc();
void rm_proc();
void init_env_vars();
void rm_env_var();
int check_process_commands (int paramN, char* commmand[]);

void new_process (char* name, pid_t pid);

void cmd_uid (int paramN, char* command[]);
void cmd_showvar (int paramN, char* command[]);
void cmd_changevar (int paramN, char* command[]);
void cmd_subsvar (int paramN, char* command[]);
void cmd_showenv (int paramN, char* command[]);
void cmd_fork (int paramN, UNUSED char* command[]); 
void cmd_exec (int paramN, char* command[]);
void cmd_jobs (int paramN, char* command[]);
void cmd_deljobs (int paramN, char* command[]);
void cmd_job (int paramN, char* command[]);

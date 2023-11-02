#pragma once

void init_file_list();
void rm_file_list();
int check_file_commands(int paramN, char* command[]);

void cmd_open (int paramN, char* params[]);
void cmd_close (int paramN, char* params[]);
void cmd_dup (int paramN, char* params[]);
void cmd_listopen (int paramN, char* params[]);
void cmd_create(int paramN, char* params[]);
void cmd_delete(int paramN, char* params[]);
void cmd_deltree(int paramN, char* params[]);


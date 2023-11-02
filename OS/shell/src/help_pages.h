#pragma once

void cmd_help (int paramN, char* params[]);
int is_help_param (int paramN, char* command[]);

void list_commands();
void help_help ();
void help_authors();
void help_pid();
void help_chdir();
void help_infosys();
void help_quit();
void help_date();
void help_time();
void help_hist();
void help_command();
void help_open();
void help_close();
void help_dup();
void help_listopen();
void help_create();
void help_stat();
void help_list();
void help_delete();
void help_deltree();


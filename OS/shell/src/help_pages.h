/*
 * Name: Siyuan He              Login: siyuan.he
 * Name: Paula Taibo Suárez     Login: p.taibo
 */

#pragma once

void cmd_help (int paramN, char* params[]);
// Checks if parameter is one of the global help parameters
// -? or -help
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
void help_malloc();
void help_shared();
void help_mmap();
void help_read();
void help_write();
void help_memdump();
void help_memfill();
void help_mem();
void help_recurse();
void help_uid();
void help_showvar();
void help_changevar();
void help_subsvar();
void help_showenv();
void help_fork();
void help_exec();
void help_jobs();
void help_deljobs();
void help_job();


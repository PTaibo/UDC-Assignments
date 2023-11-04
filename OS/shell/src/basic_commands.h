#pragma once

// Check if a command is implemented in the file
int check_basic_commands (int paramN, char* command[]);

// Prints authors' name and login
void cmd_authors (int paramN, char* params[]);

//Prints shell's or parent process' pid
void cmd_pid (int paramN, char* params[]);

// Print cwd or change directory
void cmd_chdir  (int paramN, char* params[]);

// Print current date
void cmd_date  (int paramN, char* params[]);

// Print current time
void cmd_time (int paramN, char* params[]);

// Print system information
void cmd_infosys (int paramN, char* params[]);

// Exit shell
void cmd_quit (int paramN, char* params[]);

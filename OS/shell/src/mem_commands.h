#pragma once

// Check if a command is implemented in the file
int check_mem_commands (int paramN, char* command[]);

void cmd_malloc(int paramN, char* params[]);
void cmd_shared(int paramN, char* params[]);
void cmd_mmap(int paramN, char* params[]);
void cmd_read(int paramN, char* params[]);
void cmd_write(int paramN, char* params[]);
void cmd_memdump(int paramN, char* params[]);
void cmd_memfill(int paramN, char* params[]);
void cmd_mem(int paramN, char* params[]);
void cmd_recurse(int paramN, char* params[]);


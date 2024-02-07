/*
 * Name: Siyuan He              Login: siyuan.he
 * Name: Paula Taibo Suárez     Login: p.taibo
 */

#pragma once

// Initialize list of opened files
void init_file_list();
// Free all elements in file list and close files
void rm_file_list();
// Check if a command is implemented in the file
int check_file_commands(int paramN, char* command[]);

// Open a file with the specified mode
void cmd_open (int paramN, char* params[]);
// Close a file
void cmd_close (int paramN, char* params[]);
// Duplicate file descriptor
void cmd_dup (int paramN, char* params[]);
// Print list of opened files
void cmd_listopen (int paramN, char* params[]);
// Create new file or directory
void cmd_create(int paramN, char* params[]);
// Delete a file or directory
void cmd_delete(int paramN, char* params[]);
// Delete a directory recursively
void cmd_deltree(int paramN, char* params[]);


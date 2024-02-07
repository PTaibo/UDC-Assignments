/*
 * Name: Siyuan He              Login: siyuan.he
 * Name: Paula Taibo Suárez     Login: p.taibo
 */

#pragma once

// Initialize history list
void init_history();
// Free memory in history list
void rm_history();
// Check if a command is implemented in the file
int check_history_commands (int paramN, char* command[]);
// Add inserted command to history
void add_history_entry(char* command);

// Print or clear the history
void cmd_hist (int paramN, char* params[]);
// Repeat a command from history
void cmd_repeat (int paramN, char* params[]);

#pragma once

void init_history();
int check_history_commands (int paramN, char* command[]);
void add_history_entry(char* command);

void cmd_hist (int paramN, char* params[]);
void cmd_repeat (int paramN, char* params[]);

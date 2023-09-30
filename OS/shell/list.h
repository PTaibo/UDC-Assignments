#pragma once

#include <string.h>
#define MAX_ELEMENTS 4096

typedef struct {
    int start, end;
    char* elements[MAX_ELEMENTS];
} List;

char* make_cpy (char* element);

// History-specific methods
void initialize_hist (List* newList);
void clear_list (List* list);
void append_element (char* element, List* list);
int print_n_elements (int n, List* list);
char* get_command (int pos, List* list);

// File-specific methods
void initialize_file_list (List* newList);
char* get_file (int pos, List* list);
int add_element (int pos, char* element, List* list);
int delete_element (int pos, List* list);
int dup_element (int pos, List* list);
int get_next_fd (int pos, List* list);


#pragma once

#include <string.h>
#define null -1
#define MAX_ELEMENTS 4096

typedef struct {
    char* elements[MAX_ELEMENTS];
    int start, end;
} List;

void create_list(List* newList);
int is_empty_list(List* list);

void clear_list(List* list);
int print_n_elements(int n, List* list);
char* get_element(int pos, List* list);
int add_element(int pos, char* element, List* list);
int delete_element(int pos, List* list);


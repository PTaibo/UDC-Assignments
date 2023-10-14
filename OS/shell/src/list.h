#pragma once

#include <string.h>
#define MAX_ELEMENTS 4096

typedef struct {
    int start, end;
    char* elements[MAX_ELEMENTS];
} basic_list;

typedef struct {
    char* elements[MAX_ELEMENTS];
} file_list;

// History-specific methods
void basicList_initialize (basic_list* newList);
void basicList_clear (basic_list* list);
void basicList_append (char* element, basic_list* list);
int basicList_print (int n, basic_list* list);
char* basicList_getter (int pos, char* dest, basic_list* list);

// File-specific methods
void fileList_initialize (file_list* newList);
void fileList_clear (file_list* list);
char* fileList_getter (int pos, char* dest, file_list* list);
int fileList_add (int pos, char* element, file_list* list);
int fileList_delete (int pos, file_list* list);
int fileList_dup (int pos, file_list* list);
int fileList_nextFD (int pos, file_list* list);


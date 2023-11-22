#pragma once

#include "types.h"

#include <string.h>
#define MAX_ELEMENTS 4096

typedef struct {
    int start, end;
    char* elements[MAX_ELEMENTS];
} basic_list;

typedef struct {
    char* elements[MAX_ELEMENTS];
} file_list;

struct node {
    struct node* next;
    void* info;
};
typedef struct node* Pos;
typedef struct node* DynamicList;

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

// Memory specific methods
void dynList_init (DynamicList newList);
int dynList_isEmpty (DynamicList list);
void dynList_clear (DynamicList list);

int dynList_add (void* element, DynamicList list);
void dynList_delete (Pos list);

Pos dynList_first (Pos pos);
Pos dynList_next (Pos pos);
void* dynList_getter (Pos pos);


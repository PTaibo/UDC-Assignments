#include "list.h"

#include <stdio.h>
#include <stdlib.h>

char* make_cpy (char* src, char* dest)
{
    if (dest == NULL)
        dest = malloc(strlen(src) + 1);
    strcpy(dest, src);
    return dest;
}

// History-specific methods

void initialize_hist (List* newList)
{
    newList->start = -1;
    newList->end = -1;
}

void clear_list (List* list)
{
    if (list->start == -1)
        return;

    for (int i = list->start; i < list->end; i++){
        free(list->elements[i]);
        list->elements[i] = NULL;
    }

    initialize_hist(list);
}

void append_element (char* element, List* list)
{
    if (list->start == -1) {
        list->start = list->end = 0;
        list->elements[0] = make_cpy(element, NULL);
        return;
    }

    list->end = (list->end + 1) % MAX_ELEMENTS;
    list->elements[list->end] = make_cpy(element, NULL);

    if (list->end == list->start){
        list->start++;
    }
}

int get_size (List* list)
{
    if (list->end < list->start)
        return MAX_ELEMENTS;

    return list->end + 1;
}

int print_n_elements (int n, List* list)
{
    if (list->start < 0 || n > get_size(list))
        return -1;

    int end;

    if (n == -1)
        end = list->end;
    else
        end = list->start + n - 1;

    int cnt = 0;
    for (int i = list->start; i != end; i = (i+1)%MAX_ELEMENTS, cnt++){
        printf("%5d  %s", cnt, list->elements[i]);
    }
    printf("%5d  %s", cnt, list->elements[end]);

    return 0;
}

char* get_command (int pos, char* dest, List* list)
{
    int list_pos = (pos - list->start) % MAX_ELEMENTS;

    return make_cpy(list->elements[list_pos], dest);
}

// File-list-specific methods

void initialize_file_list (List* newList)
{
    newList->start = 0;
    newList->end = MAX_ELEMENTS - 1;

    newList->elements[0] = "stdin";
    newList->elements[1] = "stdout";
    newList->elements[2] = "stderr";
    for (int i = 3; i < MAX_ELEMENTS; i++){
        newList->elements[i] = NULL;
    }
}

char* get_file(int pos, char* dest, List* list)
{
    if (pos < 0 || pos > MAX_ELEMENTS - 1)
        return NULL;

    return make_cpy(list->elements[pos], dest);
}

int add_element (int pos, char* element, List* list)
{
    if (pos < 0 || pos >= MAX_ELEMENTS){
        return -1;
    }

    if (list->elements[pos] != NULL){
        return -1;
    }

    list->elements[pos] = malloc(strlen(element) + 1);
    if (list->elements[pos] == NULL){
        printf("Could not allocate memory\n");
        return -1;
    }
    strcpy(list->elements[pos], element);

    return 0;
}

int delete_element (int pos, List* list)
{
    if (pos < 0 || pos >= MAX_ELEMENTS){
        return -1;
    }

    if (list->elements[pos] == NULL)
        return -1; //TODO: -1 o 0???

    free(list->elements[pos]);
    list->elements[pos] = NULL;

    return 0;
}

int dup_element (int pos, List* list)
{
    for (int i = 0; i < MAX_ELEMENTS - 1; i++){
        if (list->elements[i] == NULL){
            list->elements[i] = list->elements[pos];
            return 0;
        }
    }

    return -1;
}

int get_next_fd (int pos, List* list)
{
    for (int i = pos+1; i < MAX_ELEMENTS - 1; i++){
        if (list->elements[i] != NULL){
            return i;
        }
    }
    return -1;
}


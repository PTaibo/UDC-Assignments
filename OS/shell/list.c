#include "list.h"

#include <stdio.h>
#include <stdlib.h>

#include "error_msgs.h"

// Generic functions

char* make_cpy (char* src, char* dest)
{
    if (dest == NULL){
        dest = malloc(strlen(src) + 1);
        if (dest == NULL){
            mem_fail();
            return NULL;
        }
    }
        
    strcpy(dest, src);
    return dest;
}

// Basic list implementation

void basicList_initialize (basic_list* newList)
{
    newList->start = -1;
    newList->end = -1;
}

void basicList_clear (basic_list* list)
{
    if (list->start == -1)
        return;

    for (int i = list->start; i < list->end; i++){
        free(list->elements[i]);
        list->elements[i] = NULL;
    }

    basicList_initialize(list);
}

int basicList_size (basic_list* list)
{
    if (list->start == -1)
        return 0;

    if (list->end >= list->start){
        return list->end - list->start + 1;
    }

    return MAX_ELEMENTS - list->start + list->end;
}

int basicList_pos (int pos, basic_list* list)
{
    if (pos >= basicList_size (list))
        return -1;

    if (list->end >= list->start){
        return list->start + pos;
    }

    if (pos <= MAX_ELEMENTS - list->start){
        return list->start + pos;
    }

    pos -= MAX_ELEMENTS - list->start;
    return pos;
}

void basicList_append (char* element, basic_list* list)
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

int basicList_print (int n, basic_list* list)
{
    if (list->start < 0 || n > basicList_size(list))
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

char* basicList_getter (int pos, char* dest, basic_list* list)
{
    int list_pos = basicList_pos (pos, list);

    if (list_pos < 0){
        return NULL;
    }

    return make_cpy(list->elements[list_pos], dest);
}

// File list implementation

void fileList_initialize (file_list* newList)
{
    newList->elements[0] = "stdin";
    newList->elements[1] = "stdout";
    newList->elements[2] = "stderr";
    for (int i = 3; i < MAX_ELEMENTS; i++){
        newList->elements[i] = NULL;
    }
}

void fileList_clear (file_list* list)
{
    for (int i = 0; i < MAX_ELEMENTS; i++){
        if (list->elements[i] != NULL){
            free(list->elements[i]);
            list->elements[i] = NULL;
        }
    }
}

char* fileList_getter (int pos, char* dest, file_list* list)
{
    if (pos < 0 || pos > MAX_ELEMENTS - 1)
        return NULL;

    return make_cpy(list->elements[pos], dest);
}

int fileList_add (int pos, char* element, file_list* list)
{
    if (pos < 0 || pos >= MAX_ELEMENTS){
        printf("Shouldn't enter this condition\n");
        return -1;
    }

    if (list->elements[pos] != NULL){
        return -1;
    }

    list->elements[pos] = make_cpy(element, NULL);

    return 0;
}

int fileList_delete (int pos, file_list* list)
{
    if (pos < 3 || pos >= MAX_ELEMENTS){
        return -1;
    }

    if (list->elements[pos] == NULL)
        return 0;

    free(list->elements[pos]);
    list->elements[pos] = NULL;

    return 0;
}

int fileList_dup (int pos, file_list* list)
{
    for (int i = 0; i < MAX_ELEMENTS; i++){
        if (list->elements[i] == NULL){
            list->elements[i] = make_cpy(list->elements[pos], NULL);
            return 0;
        }
    }

    return -1;
}

int fileList_nextFD (int pos, file_list* list)
{
    for (int i = pos+1; i < MAX_ELEMENTS; i++){ // Estaba antes con -1 (???)
        if (list->elements[i] != NULL){
            return i;
        }
    }
    return -1;
}


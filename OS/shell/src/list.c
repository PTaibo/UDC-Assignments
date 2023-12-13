#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error_msgs.h"

// Generic functions

// strdup
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

/*
 * Basic list is based on the idea that you cannot 
 * remove independent elements from the history.
 * It fills like a normal list and, when full, starts
 * to cycle, removing one element from the start to
 * insert the element from the end. Once its cleared,
 * it returns to behaving like a normal list, where
 * only the tail moves.
 * Since you don't remove elements, the head is always
 * going to be in position 0 except when full.
 */

void basicList_initialize (basic_list* newList)
{
    newList->start = -1;
    newList->end = -1;
}

void basicList_clear (basic_list* list)
{
    if (list->start == -1)
        return;

    for (int i = list->start; i <= list->end; i++){
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
        printf("%5d  %s\n", cnt, list->elements[i]);
    }
    printf("%5d  %s\n", cnt, list->elements[end]);

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
    newList->elements[0] = strdup("stdin");
    newList->elements[1] = strdup("stdout");
    newList->elements[2] = strdup("stderr");
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
    if (pos >= MAX_ELEMENTS){
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

// Dynamic list implementation

/*
 * Positions start at 0
 */

typedef struct node node;

void dynList_init (node** newList)
{
    *newList = NULL;
}

int dynList_isEmpty (node* list)
{
    return list == NULL;
}

void dynList_clear (void (*d)(void* info), node **list)
{
    while (*list != NULL){
        node* next = (*list)->next;
        if (d != NULL)
            d((*list)->info);
        free((*list)->info);
        free(*list);
        *list = next;
    }
}

int dynList_add (void* element, node **list)
{
    node* newNode = malloc(sizeof(node));
    if (newNode == NULL) return 0;
    newNode->info = element;
    newNode->prev = NULL;

    if (dynList_isEmpty(*list))
        newNode->next = NULL;
    else {
        newNode->next = *list;
        (*list)->prev = newNode;
    }

    *list = newNode;
    return 1;
}

void dynList_delete (void (*d)(void* info), node *pos, node** list)
{
    if (pos == NULL) return;

    if (pos->prev != NULL)
        pos->prev->next = pos->next;
    else
        *list = pos->next;

    if (pos->next != NULL)
        pos->next->prev = pos->prev;

    if (pos->info != NULL){
        if (d != NULL)
            d(pos->info);
        free(pos->info);
    }
    free(pos);
}

node* dynList_first (node* list)
{
    return list;
}

node* dynList_next (node** pos)
{
    return (*pos)->next;
}

void dynList_fwd(node** pos)
{
    *pos = (*pos)->next;
}

void* dynList_getter (node* pos)
{
    return pos->info;
}


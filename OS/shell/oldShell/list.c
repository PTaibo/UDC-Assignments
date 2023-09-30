#include "list.h"
#include <stdlib.h>
#include <stdio.h>

void create_list(List newList)
{
    newList.start = -1;
    newList.end = 0;
}

int is_empty_list (List list)
{
    return list.start < 0;
}

void clear_list (List list)
{
    if (is_empty_list(list))
            return;

    for (int i = list.start; i < list.end; i++){
        free(list.elements[i]);
        list.elements[i] = NULL;
    }

    list.start = -1;
    list.end = 0;
}

int print_n_elements (int n, List list)
{
    if (n == null){
        n = list.end - list.start;
    }

    if (n >= list.end - list.start)
        return -1;

    for (int i = 0; i < n; i++){
        printf("\t%s\n", list.elements[i]);
    }

    return 0;
}

char* get_element (int pos, List list)
{
    if (pos >= (list.end - list.start) || pos < 0){
        return NULL;
    }

    return list.elements[list.start+pos];
}

int valid_pos (int pos, List list)
{
    if (pos > (list.end - list.start) || pos < 0){
        return 0;
    }

    return 1;
}

int add_element (int pos, char* element, List list)
{
    if (pos == null){
        pos = list.end;
    }

    if (!valid_pos(pos, list))
        return -1;

    if (list.elements[pos] != NULL){
       return -1;
    }

    list.elements[pos] = element;
    return 0;
}

int delete_element (int pos, List list)
{
    if (!valid_pos(pos, list))
        return -1;

    if (list.elements[pos] == NULL)
        return 0;

    free(list.elements[pos]);
    list.elements[pos] = NULL;

    if (pos == list.end - 1)
        list.end = pos;

    return 1;
}



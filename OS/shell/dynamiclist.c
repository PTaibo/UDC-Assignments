#include <stdio.h>
#include <string.h>
#include "dynamiclist.h"
#define UNUSED __attribute__((unused)) //Gets rid of unused parameter warnings


void createEmptyList(tList* newList){
    newList = NULL;
}

int isEmptyList(tList list)
{
    return list == NULL;
}

tPosL first (tList list)
{
    return list;
}

tPosL last (tList list)
{
    tNode* it;
    for (it = list; it ->next != NULL; it = it->next);
    return it;
}

tPosL next (tPosL pos, UNUSED tList list)
{
    return pos->next;
}

tPosL previous (tPosL pos, tList list)
{
    if (pos == list){
        return NULL;
    }
    tNode* it;
    for (it = list; it -> next != pos; it = it->next);
    return it;
}

void insertItem (void *data, tList* list)
{
    //CREATE NEW NODE
    tNode* tmp;
    tmp = malloc(sizeof(tNode));
    if (tmp == NULL) //Check if there was space left to create it
        return 0;
    tmp->next = NULL;
    tmp->element = data;

    //ADD NODE TO LIST
    //Case: empty list
    if (*list == NULL){
        *list = tmp;
        return 1;
    }

    //Case: at the end
    tNode* lastE = last(*list);
    lastE->next = tmp;
    return 1;
}

void deleteAtPosition(tPosL pos, tList* list)
{
    //Case 1: delete first element
    if (pos == *list){
        *list = pos->next;
        free(pos);
        return;
    }

    //Case 2: delete last or intermediate element
    tNode* prev = previous(pos, *list);
    prev->next = pos->next;
    free(pos);
    return;
}

void *getItem (tPosL pos, UNUSED tList list)
{
    if (pos==NULL)
        return NULL;
    else
        return pos->element;
}

tPosL findItem (void *element, tList list)
{
    for (tNode* it = list; it != NULL; it = it->next){
        if (it->element == element)
            return it;
    }
    return NULL;
}

void clearList(tList* list) {
    tPosL pos = *list;
    tPosL nextp;

    while (pos != NULL) {
        nextp = pos->next;  // It kepts the next pos to change after
        free(pos);
        pos = next;  // Move to the next position
    }

    *list = NULL;  // It sets the list so it can be checked later to be emtpy
}


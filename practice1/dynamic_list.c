/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: ***************************** LOGIN 1: **********
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
 * DATE: ** / ** / **
 */

#include "dynamic_list.h"

void createEmptyList(tList* newList)
{
    newList->first = LNULL;
    newList->lastPos = LNULL;
}

int isEmptyList(tList list)
{
    return list.first == LNULL;
}

tPosL first (tList list)
{
    return list.first;
}

tPosL last (tList list)
{
    return list.lastPos;
}

tPosL next (tPosL pos, tList list)
{
    return pos->next;
}

tPosL previous (tPosL pos, tList list)
{
    return pos->prev;
}

int insertItem (tItemL item, tPosL pos, tList* list)
{
    //CREATE NEW NODE
    tNode* tmp;
    tmp = malloc(sizeof(tNode));
    if (tmp == LNULL) //Check if there was space left to create it
        return 0;
    tmp->prev = LNULL;
    tmp->next = LNULL;
    tmp->element = item;

    //ADD NODE TO LIST
    //Case 1: empty list
    if (list->first == LNULL){
        list->first = tmp;
        list->lastPos = tmp;
        return 1;
    }

    //Case 2: add to end of list
    if (pos == LNULL){
        tmp->prev = list->lastPos;
        list->lastPos->next = tmp;
        list->lastPos = tmp;
        return 1;
    }
    
    //Case 3: add to the beginning of the list
    if (pos == list->first){
        tmp->next = pos;
        list->first = tmp;
        pos->prev = tmp;
        return 1;
    }

    //Case 4: add to middle of list
    tmp->next = pos;
    tmp->prev = pos->prev;
    pos->prev = tmp;
    tmp->prev->next = tmp;
    return 1;    
}

void deleteAtPosition(tPosL pos, tList* list)
{
    //Case 1: delete first element
    if (pos == list->first){
        list->first = pos->next;
        if (pos != list->lastPos) //In case it is the only element in the list
            pos->next->prev = LNULL;
        free(pos);
        return;
    }

    //Case 2: delete last element
    if (pos == list->lastPos){
        pos->prev->next = LNULL;
        list->lastPos = pos->prev;
        free(pos);
        return;
    }

    //Case 3: delete in-between element
    pos->prev->next = pos->next;
    pos->next->prev = pos->prev;
    free(pos);
}

tItemL getItem (tPosL pos, tList list)
{
    return pos->element;
}

void updateItem (tItemL item, tPosL pos, tList* list)
{
    pos->element = item;
}

tPosL findItem (tParticipantName participant, tList list)
{
    for (tNode* it = list.first; it != NULL; it = it->next){
        if (!strcmp(it->element.participantName, participant))
            return it;
    }
    return LNULL;
}

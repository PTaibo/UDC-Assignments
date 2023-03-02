/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: PAULA TAIBO SUÁREZ LOGIN 1: P.TAIBO
 * AUTHOR 2: SIYUAN HE LOGIN 2: SIYUAN.HE
 * GROUP: 6.1
 * DATE: 16 / 02 / 23
 */

#include "static_list.h"

void createEmptyList(tList *newList)
{
    newList->lastPos = LNULL;
}

bool isEmptyList(tList list)
{
    return list.lastPos==LNULL;
}

tPosL first(tList list)
{
    return 0;
}

tPosL last(tList list)
{
    return list.lastPos;
}

tPosL next(tPosL pos, tList list)
{
    if (pos == list.lastPos)
        return LNULL;
    // else return pos+1;
    return pos + 1;
}

tPosL previous(tPosL pos, tList list)
{
    if (pos == 0)
        return LNULL;
    return pos - 1;
}

bool insertItem(tItemL item, tPosL pos, tList *list)
{
    if (list->lastPos == MAX_LIST - 1){
        return 0;
    }
    if (pos == LNULL){
        list->lastPos++;
        list->elements[list->lastPos] = item;
        return 1;
    }

    for (int i = list->lastPos; i >= pos; i--)
        list->elements[i+1] = list->elements[i];

    list->elements[pos]=item;
    list->lastPos++;
    return 1;
}

void deleteAtPosition(tPosL pos, tList* list)
{
    list->lastPos--;
    for (int i=pos;i<=list->lastPos;i++)
            list->elements[i]=list->elements[i+1];   
}

tItemL getItem(tPosL pos, tList list)
{
    return list.elements[pos];
}

void updateItem (tItemL item, tPosL pos, tList* list)
{
    list->elements[pos]=item;
}

tPosL findItem (tParticipantName participant, tList list)
{
    for (int i=0;i<=list.lastPos;i++){
        if(strcmp(list.elements[i].participantName,participant)==0)
            return i;
    }
    return LNULL;
}
/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: PAULA TAIBO SUÁREZ LOGIN 1: P.TAIBO
 * AUTHOR 2: SIYUAN HE LOGIN 2: SIYUAN.HE
 * GROUP: 6.1
 * DATE: 16 / 02 / 23
 */

#include "static_list.h"
#define UNUSED __attribute__((unused)) //Gets rid of unused parameter warnings

void createEmptyList(tList *newList)
{
    newList->lastPos = LNULL; //we set the last position as -1 so the next is the position 0.
}

bool isEmptyList(tList list) 
{
    return list.lastPos==LNULL;//if it is -1 then it will retrun true otherwise it will be false
}

tPosL first(UNUSED tList list)
{
    return 0;//the first element in a array is 0.
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

tPosL previous(tPosL pos, UNUSED tList list)
{
    if (pos == 0)
        return LNULL;
    return pos - 1;
}

bool insertItem(tItemL item, tPosL pos, tList *list)
{
    if (list->lastPos == MAX_LIST - 1){//Cheking if the list is full
        return 0;
    }
    if (pos == LNULL){//By the specs
        ++(list->lastPos);
        list->elements[list->lastPos] = item;
        return 1;
    }

    for (int i = list->lastPos; i >= pos; i--)//we move the elememts one behind until the position inserted
        list->elements[i+1] = list->elements[i];

    list->elements[pos]=item;//We put the item in the position
    ++(list->lastPos);
    return 1;
}

void deleteAtPosition(tPosL pos, tList* list)
{
    for (int i=pos;i<=list->lastPos;i++)//we move one previus to lap the position
            list->elements[i]=list->elements[i+1];  
    --(list->lastPos); //we quit one position
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
    for (int i=0;i<=list.lastPos;i++){//we go through the list
        if(strcmp(list.elements[i].participantName,participant)==0)
        //strcmp returns 0 if it is equal
            return i;
    }
    return LNULL;//If it doesnt find it it will retrun -1
}
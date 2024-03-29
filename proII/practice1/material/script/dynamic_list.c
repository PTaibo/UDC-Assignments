/*
 * TITLE: PROGRAMMING II LABS       * SUBTITLE: Practical 1
 * AUTHOR 1: Siyuan He              * LOGIN 1: siyuan.he
 * AUTHOR 2: Paula Taibo Suárez     * LOGIN 2: p.taibo
 * GROUP: 6.1                       * DATE: 02 / 03 / 23
 */

#include "dynamic_list.h"
#define UNUSED __attribute__((unused)) //Gets rid of unused parameter warnings

void createEmptyList(tList* newList)
{
    *newList = LNULL;
}

int isEmptyList(tList list)
{
    return list == LNULL;
}

tPosL first (tList list)
{
    return list;
}

tPosL last (tList list)
{
    tNode* it;
    for (it = list; it ->next != LNULL; it = it->next);
    return it;
}

tPosL next (tPosL pos, UNUSED tList list)
{
    return pos->next;
}

tPosL previous (tPosL pos, tList list)
{
    if (pos == list){
        return LNULL;
    }
    tNode* it;
    for (it = list; it -> next != pos; it = it->next);
    return it;
}

int insertItem (tItemL item, tPosL pos, tList* list)
{
    //CREATE NEW NODE
    tNode* tmp;
    tmp = malloc(sizeof(tNode));
    if (tmp == LNULL) //Check if there was space left to create it
        return 0;
    tmp->next = LNULL;
    tmp->element = item;

    //ADD NODE TO LIST
    //Case 1: empty list
    if (*list == LNULL){
        *list = tmp;
        return 1;
    }

    //Case 2: add to end of list
    if (pos == LNULL){
        tNode* lastE = last(*list);
        lastE->next = tmp;
        return 1;
    }
    
    //Case 3: add to the beginning of the list
    if (pos == *list){
        tmp->next = pos;
        *list = tmp;
        return 1;
    }

    //Case 4: add to middle of list
    tmp->element = pos->element;
    tmp->next = pos->next;
    pos->element = item;
    pos->next = tmp;
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

tItemL getItem (tPosL pos, UNUSED tList list)
{
    return pos->element;
}

void updateItem (tItemL item, tPosL pos, UNUSED tList* list)
{
    pos->element = item;
}

tPosL findItem (tParticipantName participant, tList list)
{
    for (tNode* it = list; it != NULL; it = it->next){
        if (!strcmp(it->element.participantName, participant))
            return it;
    }
    return LNULL;
}

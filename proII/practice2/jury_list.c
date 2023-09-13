/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Siyuan He            LOGIN 1: siyuan.he
 * AUTHOR 2: Paula Taibo Suárez   LOGIN 2: p.taibo
 * GROUP: 6.1
 * DATE: 14 / 04 / 23
 */

#include <string.h>
#include <stdio.h>

#include "jury_list.h"
#include "participant_list.h"

#define UNUSED __attribute__((unused)) //Gets rid of unused parameter warnings

void createEmptyListJ (tListJ* newList)
{
    newList->p = NULLJ;
}

bool isEmptyListJ(tListJ list)
{
    return list.p == NULLJ;
}

tPosJ firstJ(UNUSED tListJ list)
{
    return 0;
}

tPosJ lastJ (tListJ list)
{
    return list.p;
}

tPosJ nextJ (tPosJ pos, tListJ list)
{
    if (pos == list.p)
        return NULLJ;
    
    return ++pos;
}

tPosJ previousJ (tPosJ pos, UNUSED tListJ list)
{
    return --pos;
}

bool insertItemJ (tItemJ item, tListJ* list)
{
    if (list->p + 1 == MAX_LIST)
        return false;

    list->p++;

    //Case 1: empty list
    if (!list->p){
        list->jury[0] = item;
        return true;
    }

    //Case 2: goes in the middle/end of the list
    int i = list->p;

    for (i = list->p; i > 0; i--){
        if (strcmp(item.juryName, list->jury[i-1].juryName) > 0){
            list->jury[i] = item;
            return true;
        }
        list->jury[i] = list->jury[i-1];
    }
    
    //Case 3: goes at the beginning of the list
    list->jury[0] = item;
    return true;
}

void deleteAtPositionJ (tPosJ pos, tListJ* list)
{
    //Case 1: empty list
    if (list->p == NULLJ)
        return;

    //Case 2: delete last element
    if (pos == list->p){
        list->p--;
        return;
    }

    //Case 3: element in the middle or at the start
    for (int i = pos; i < list->p; i++){
        list->jury[i] = list->jury[i+1];
    }
    list->p--;
}

tItemJ getItemJ (tPosJ pos, tListJ list)
{
    return list.jury[pos];
}

void updateItemJ (tItemJ item, tPosJ pos, tListJ* list)
{
    list->jury[pos] = item;
}

tPosJ findItemJ (tJuryName judge, tListJ list)
{
    //Binary search
    int l = -1;
    int r = list.p;

    while (r > l + 1){
        int m = (l+r) / 2;

        if (strcmp(list.jury[m].juryName, judge) < 0)
            l = m;
        else
            r = m;
    }

    //Check if the element was found
    if (strcmp(list.jury[r].juryName, judge) != 0)
        return NULLJ;

    return r;
}

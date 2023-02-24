/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: PAULA TAIBO SUÁREZ LOGIN 1: P.TAIBO
 * AUTHOR 2: SIYUAN HE LOGIN 2: SIYUAN.HE
 * GROUP: 6.1
 * DATE: 16 / 02 / 23
 */

#include "static_list.h"

void createEmptyList (tList* newList)
{
    newList->lastPos = LNULL;
}

tPosL first (tList list)
{
    return 0;
}

tPosL last(tList list)
{
    return list.lastPos;
}

tPosL next (tPosL pos,tList list)
{
    if (pos==list.lastPos)
        return LNULL;
//else return pos+1;
    return pos+1;
}

tPosL previous (tPosL pos, tList list)
{
    if (pos==0)
        return LNULL;
    return pos-1;
}

bool insertItem (tItemL item, tPosL pos, tList* list)
{
    printf()
}
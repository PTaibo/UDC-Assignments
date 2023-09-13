/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: PAULA TAIBO SUÁREZ LOGIN 1: P.TAIBO
 * AUTHOR 2: SIYUAN HE LOGIN 2: SIYUAN.HE
 * GROUP: 6.1
 * DATE: 16 / 02 / 23
 */


#ifndef STATIC_LIST_H
#define STATIC_LIST_H

#include "types.h"
#include <string.h>
#define LNULL -1
#define MAX_LIST 1000

typedef int tPosL; 

typedef struct {
    tItemL elements[MAX_LIST];
    tPosL lastPos;
} tList;

void createEmptyList (tList* newList);
bool isEmptyList(tList list);
tPosL first(tList list);
tPosL last (tList list);
tPosL next (tPosL pos, tList list);
tPosL previous (tPosL pos, tList list);
bool insertItem (tItemL item, tPosL pos, tList* list);
void deleteAtPosition(tPosL pos, tList* list);
tItemL getItem(tPosL pos, tList list);
void updateItem (tItemL item, tPosL pos, tList* list);
tPosL findItem (tParticipantName participant, tList list);

#endif

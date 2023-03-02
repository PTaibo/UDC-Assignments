/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: ***************************** LOGIN 1: **********
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
 * DATE: ** / ** / **
 */

#ifndef DYNAMIC_LIST_H
#define DYNAMIC_LIST_H

#include "types.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#define LNULL NULL
#define MAX_LIST 1000

typedef struct node tNode;

struct node {
    tItemL element;
    tNode* next;
};

typedef tNode* tList;
typedef tNode* tPosL;

void createEmptyList(tList* newList);
int isEmptyList(tList list);
tPosL first (tList list);
tPosL last (tList list);
tPosL next (tPosL pos, tList list);
tPosL previous (tPosL pos, tList list);
int insertItem (tItemL item, tPosL pos, tList* list);
void deleteAtPosition(tPosL pos, tList* list);
tItemL getItem (tPosL pos, tList list);
void updateItem (tItemL item, tPosL pos, tList* list);
tPosL findItem (tParticipantName participant, tList list);

#endif

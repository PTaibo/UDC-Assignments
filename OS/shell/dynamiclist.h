#pragma once


typedef struct node tNode;

struct node {
    void *element;
    struct node *next;
};

typedef tNode* tList;
typedef tNode* tPosL;

void createEmptyList(tList* newList);
int isEmptyList(tList list);
tPosL first (tList list);
tPosL last (tList list);
tPosL next (tPosL pos, tList list);
tPosL previous (tPosL pos, tList list);
void insertItem (void *data, tList* list);
void deleteAtPosition(tPosL pos, tList* list);
void *getItem (tPosL pos, tList list);
tPosL findItem (void *element, tList list);
void clearList (tList* list);


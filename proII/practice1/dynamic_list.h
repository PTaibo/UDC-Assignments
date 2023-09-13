/*
 * TITLE: PROGRAMMING II LABS       * SUBTITLE: Practical 1
 * AUTHOR 1: Siyuan He              * LOGIN 1: siyuan.he
 * AUTHOR 2: Paula Taibo Suárez     * LOGIN 2: p.taibo
 * GROUP: 6.1                       * DATE: 02 / 03 / 23
 */

#ifndef DYNAMIC_LIST_H
#define DYNAMIC_LIST_H

#include "types.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#define LNULL NULL

typedef struct node tNode;

struct node {
    tItemL element;
    tNode* next;
};

typedef tNode* tList;
typedef tNode* tPosL;

void createEmptyList(tList* newList);
/*
    Goal: creates and empty list
    Inputs: a pointer to list (tList)
    Outputs: NONE
    Preconditions: NONE
    Postconditions: the list is initialized and has no elements
*/
int isEmptyList(tList list);
/*
    Goal: determines whether the list is empty or not
    Inputs: a pointer to list (tList)
    Outputs: an int: 1 [TRUE] if it is empty and 0 [FALSE] if not.
    Preconditions: the list is initialized
    Postconditions: NONE
*/
tPosL first (tList list);
/*
    Goal: returns the position of the first element of the list
    Inputs: a pointer to list
    Outputs: a pointer to the first element of the list
    Preconditions: the list is initialized and not empty
    Postconditions: NONE
*/
tPosL last (tList list);
/*
    Goal: returns the position of the last element of the list
    Inputs: a pointer to list
    Outputs: a pointer to the last element of the list
    Preconditions: the list is initialized and not empty
    Postconditions: NONE
*/
tPosL next (tPosL pos, tList list);
/*
    Goal: returns the position of the next element or LNULL if there isn't one
    Inputs: a pointer to a position in a list and a pointer to the list
    Outputs: the position of the element next to the one given or LNULL if there isn't one
    Preconditions: the list is initialized and the given position is valid it
    Postconditions: NONE
*/
tPosL previous (tPosL pos, tList list);
/*
    Goal: returns the position of the previous element or LNULL if there isn't one
    Inputs: a pointer to a position in a list and a pointer to the list
    Outputs: the position of the element previous to the one given or LNULL if there isn't one
    Preconditions: the list is initialized and the given position is valid in it
    Postconditions: NONE
*/
int insertItem (tItemL item, tPosL pos, tList* list);
/*
    Goal: inserts in the given position in the list an element containing the data item
    Inputs: the data item, a pointer to the position in the list and a pointer to the list
    Outputs: an int: 1 [TRUE] if it could be inserted and 0 [FALSE] if not
    Preconditions: the list is initialized and the position is valid in it or LNULL
    Postconditions: the data item is inserted before the one in the given possition or at the end if pos was LNULL
*/
void deleteAtPosition(tPosL pos, tList* list);
/*
    Goal: deletes the element at the given position from the list
    Inputs: a pointer to the element and the list
    Outputs: NONE
    Preconditions: the list is initialized and the position is valid in it
    Postconditions: the element is deleted from the list
*/
tItemL getItem (tPosL pos, tList list);
/*
    Goal: returns the content of the element at the indicated position
    Inputs: a pointer to a position in a list and a pointer to the list
    Outputs: the element in that position
    Preconditions: the list is initialized and the position is valid in it
    Postconditions: NONE
*/
void updateItem (tItemL item, tPosL pos, tList* list);
/*
    Goal: modifies the content of the element at the indicated position
    Inputs: the new content, a pointer to the position of the element to modify and a pointer to the list
    Outputs: NONE
    Preconditions: the list is initialized and the position is valid in it
    Postconditions: the order of the elements in the list is not modified
*/
tPosL findItem (tParticipantName participant, tList list);
/*
    Goal: returns the position of the first element in the list with the requested participant name
    Intputs: the participant name to look for and a pointer to the list
    Outputs: a pointer to the position of the element with the participant or LNULL if there isn't one
    Preconditions: the list is initialized
    Postconditions: NONE
*/

#endif

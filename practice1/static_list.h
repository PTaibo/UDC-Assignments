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
#include <strings.h>
#define LNULL -1
#define MAX_LIST 1000

typedef int tPosL; 

typedef struct {
    tItemL elements[MAX_LIST];
    tPosL lastPos;
} tList;

void createEmptyList (tList* newList);
/*
    Goal:create an empty list
    Inputs: a pointer to a list (tList)
    Outputs:NONE
    Preconditions:NONE
    Postconditions:The list is initialized and has no elements
*/
bool isEmptyList(tList list);
/*
    Goal:determines whether the list is empty or not
    Inputs: a list (tList)
    Outputs: if it is empty true else false
    Preconditions:the list is initialized
    Postconditions:NONE
*/
tPosL first(tList list);
/*
    Goal:returns the position of the first element of the list
    Inputs: a list (tList)
    Outputs: an integer of the position of the fist element
    Preconditions:the list is initialized and not empty
    Postconditions:NONE
*/
tPosL last (tList list);
/*
    Goal:returns the position of the last element of the list
    Inputs: a list (tList)
    Outputs: an integer of the position of the last element
    Preconditions:the list is initialized and not empty
    Postconditions:NONE
*/
tPosL next (tPosL pos, tList list);
/*
    Goal:returns the following position in the list in respect of the indicated position
    Inputs: a list (tList) and a position
    Outputs: The next position of the list or LNULL if it has no next element
    Preconditions:the list is initialized and the indicated position is a valid position in the list
    Postconditions:NONE
*/
tPosL previous (tPosL pos, tList list);
/*
    Goal:returns the previous postion in the list in respect of the indicated position
    Inputs: a list (tList) and a position
    Outputs: the previous position of the list or LNULL if it has no previous element
    Preconditions:the list is initialized and the indicated position is a valid position in the list
    Postconditions:NONE
*/
bool insertItem (tItemL item, tPosL pos, tList* list);
/*
    Goal: insert an element containing the data item at a position in the list
    Inputs: an elemet of data item type, a postion and a pointer to the list
    Outputs: if it is inserted true else false
    Preconditions:the list is initialized, it is a valid position in the list or a LNULL position
    Postconditions: The data is inserted at the indicated position or at the end if the position is LNULL
*/
void deleteAtPosition(tPosL pos, tList* list);
/*
    Goal: deletes the element at the given postion form the list
    Inputs: a pointer to a list (tList) and a position
    Outputs: NONE
    Preconditions:the list is initialized and the indicated position is a valid position in the list
    Postconditions:The positions of the elements in the list following that of the deleted one may have varied
*/
tItemL getItem(tPosL pos, tList list);
/*
    Goal:returs the content of the element at the indicated position
    Inputs: a list (tList) and a position
    Outputs: the element of data item type at the indicated position
    Preconditions:the list is initialized and the indicated position is a valid position in the list
    Postconditions:NONE
*/
void updateItem (tItemL item, tPosL pos, tList* list);
/*
    Goal: Modifies the content of the element at the indicated position
    Inputs: a pointer to a list (tList), a item of data item type and a position
    Outputs:NONE
    Preconditions:the list is initialized and the indicated position is a valid position in the list
    Postconditions:The order of the elements in the list has not been modified
*/
tPosL findItem (tParticipantName participant, tList list);
/*
    Goal:Returns the position of the first element in the list whose participant name matches the given one
    Inputs: a participant name and a list
    Outputs: an integer of the position where the name match at first time or LNULL if there is no such element
    Preconditions:the list is initialized.
    Postconditions:NONE
*/

#endif

/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Siyuan He            LOGIN 1: siyuan.he
 * AUTHOR 2: Paula Taibo Suárez   LOGIN 2: p.taibo
 * GROUP: 6.1
 * DATE: 14 / 04 / 23
 */

#ifndef JURY_LIST_H
#define JURY_LIST_H

#include "types.h"
#include "participant_list.h"

#define MAX_LIST 1000
#define NULLJ -1

typedef struct {
    tJuryName juryName;
    tNumVotes totalVoters;
    tNumVotes validVotes;
    tNumVotes nullVotes;
    tListP participantList;
} tItemJ;

typedef struct {
    int p;
    tItemJ jury[MAX_LIST];
} tListJ;

typedef int tPosJ;

void createEmptyListJ (tListJ* newList);
/*
    Goal:create an empty list
    Inputs: a pointer to a list (tList)
    Outputs:NONE
    Preconditions:NONE
    Postconditions:The list is initialized and has no elements
*/

bool isEmptyListJ(tListJ list);
/*
    Goal:determines whether the list is empty or not
    Inputs: a list (tList)
    Outputs: if it is empty true else false
    Preconditions:the list is initialized
    Postconditions:NONE
*/

tPosJ firstJ(tListJ list);
/*
    Goal:returns the position of the first element of the list
    Inputs: a list (tList)
    Outputs: an integer of the position of the fist element
    Preconditions:the list is initialized and not empty
    Postconditions:NONE
*/

tPosJ lastJ (tListJ list);
/*
    Goal:returns the position of the last element of the list
    Inputs: a list (tList)
    Outputs: an integer of the position of the last element
    Preconditions:the list is initialized and not empty
    Postconditions:NONE
*/

tPosJ nextJ (tPosJ pos, tListJ list);
/*
    Goal:returns the following position in the list in respect of the indicated position
    Inputs: a list (tList) and a position
    Outputs: The next position of the list or LNULL if it has no next element
    Preconditions:the list is initialized and the indicated position is a valid position in the list
    Postconditions:NONE
*/

tPosJ previousJ (tPosJ pos, tListJ list);
/*
    Goal:returns the previous postion in the list in respect of the indicated position
    Inputs: a list (tList) and a position
    Outputs: the previous position of the list or LNULL if it has no previous element
    Preconditions:the list is initialized and the indicated position is a valid position in the list
    Postconditions:NONE
*/

bool insertItemJ (tItemJ item, tListJ* list);
/*
    Goal: inserts the item in the list, such that the list remains ordered
    Inputs: the item (tItemJ) and the list in which to insert it (tListJ)
    Outputs: true if the function was succesfull and false otherwise
    Preconditions: the list is initialized
    Postconditions: the positions of the elements following the inserted one are changed
*/

void deleteAtPositionJ (tPosJ pos, tListJ* list);
/*
    Goal: deletes the element at the given position from the list
    Inputs: the position (tPosJ) and the list with the item to remove (tListJ)
    Outputs: NONE
    Preconditions: the list is initialized, the position is valid and the participantList is empty
    Postconditions: the positions of the elements following the deleted one are changed 
*/

tItemJ getItemJ (tPosJ pos, tListJ list);
/*
    Goal:returns the content of the element at the indicated position
    Inputs: a list (tList) and a position
    Outputs: the element of data item type at the indicated position
    Preconditions:the list is initialized and the indicated position is a valid position in the list
    Postconditions:NONE
*/

void updateItemJ (tItemJ item, tPosJ pos, tListJ* list);
/*
    Goal: Modifies the content of the element at the indicated position
    Inputs: a pointer to a list (tList), a item of data item type and a position
    Outputs:NONE
    Preconditions:the list is initialized and the indicated position is a valid position in the list
    Postconditions:The order of the elements in the list has not been modified
*/

tPosJ findItemJ (tJuryName judge, tListJ list);
/*
    Goal:Returns the position of the first element in the list whose jury name matches the given one
    Inputs: a jury name and a list
    Outputs: an integer of the position where the name match at first time or LNULL if there is no such element
    Preconditions:the list is initialized.
    Postconditions:NONE
*/

#endif

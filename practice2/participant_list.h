/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Paula Taibo Suárez LOGIN 1: p.taibo
 * AUTHOR 2: Siyuan He LOGIN 2: siyuan.he
 * GROUP: 6.1
 * DATE: 14 / 04 / 23
 */

#ifndef PARTICIPANT_LIST_H
#define PARTICIPANT_LIST_H


#include "types.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NULLP NULL

typedef struct tItemP{
    tParticipantName participantName;
    tNumVotes numVotes;
    tEUParticipant EUParticipant;
}tItemP;

typedef struct tNodeP tNodeP;

struct tNodeP{
    tItemP participant;
    tNodeP* next;
};

typedef tNodeP* tPosP;
typedef tNodeP* tListP;


//NEED TO CHANGE SPECS


void createEmptyListP (tListP* newList);
/*
    Goal: creates and empty     list
    Inputs: a pointer to list (tList)
    Outputs: NONE
    Preconditions: NONE
    Postconditions: the list is initialized and has no elements
*/
bool isEmptyListP (tListP list);
/*
    Goal: determines whether the list is empty or not
    Inputs: a pointer to list (tList)
    Outputs: an int: 1 [TRUE] if it is empty and 0 [FALSE] if not.
    Preconditions: the list is initialized
    Postconditions: NONE
*/
tPosP firstP (tListP list);
/*
    Goal: returns the position of the first element of the list
    Inputs: a pointer to list
    Outputs: a pointer to the first element of the list
    Preconditions: the list is initialized and not empty
    Postconditions: NONE
*/
tPosP lastP (tListP list);
/*
    Goal: returns the position of the last element of the list
    Inputs: a pointer to list
    Outputs: a pointer to the last element of the list
    Preconditions: the list is initialized and not empty
    Postconditions: NONE
*/
tPosP nextP (tPosP pos, tListP list);
/*
    Goal: returns the position of the next element or LNULL if there isn't one
    Inputs: a pointer to a position in a list and a pointer to the list
    Outputs: the position of the element next to the one given or LNULL if there isn't one
    Preconditions: the list is initialized and the given position is valid it
    Postconditions: NONE
*/
tPosP previousP (tPosP pos, tListP list);
/*
    Goal: returns the position of the previous element or LNULL if there isn't one
    Inputs: a pointer to a position in a list and a pointer to the list
    Outputs: the position of the element previous to the one given or LNULL if there isn't one
    Preconditions: the list is initialized and the given position is valid in it
    Postconditions: NONE
*/
bool insertItemP (tItemP item, tListP* list);
/*
    Goal: inserts in the given position in the list an element containing the data item
    Inputs: the data item, a pointer to the position in the list and a pointer to the list
    Outputs: an int: 1 [TRUE] if it could be inserted and 0 [FALSE] if not
    Preconditions: the list is initialized and the position is valid in it or LNULL
    Postconditions: the data item is inserted before the one in the given possition or at the end if pos was LNULL
*/
void deleteAtPositionP (tPosP pos, tListP* list);
/*
    Goal: deletes the element at the given position from the list
    Inputs: a pointer to the element and the list
    Outputs: NONE
    Preconditions: the list is initialized and the position is valid in it
    Postconditions: the element is deleted from the list
*/
tItemP getItemP (tPosP pos, tListP list);
/*
    Goal: returns the content of the element at the indicated position
    Inputs: a pointer to a position in a list and a pointer to the list
    Outputs: the element in that position
    Preconditions: the list is initialized and the position is valid in it
    Postconditions: NONE
*/
void updateItemP (tItemP item, tPosP pos, tListP* list);
/*
    Goal: modifies the content of the element at the indicated position
    Inputs: the new content, a pointer to the position of the element to modify and a pointer to the list
    Outputs: NONE
    Preconditions: the list is initialized and the position is valid in it
    Postconditions: the order of the elements in the list is not modified
*/
tPosP findItemP (tParticipantName participant, tListP list);
/*
    Goal: returns the position of the first element in the list with the requested participant name
    Intputs: the participant name to look for and a pointer to the list
    Outputs: a pointer to the position of the element with the participant or LNULL if there isn't one
    Preconditions: the list is initialized
    Postconditions: NONE
*/

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "siyuan.h"



void create(char *jury, int totalVoters, tListJ *juryVotesList)
{
    /*
        Goal: Add the jury with his number of votes set.
        Input: jury name, number of voters and jury list.
        Output: NONE
        Preconditions: jury's list is initialized, a valid name and a valid number of voters
        Postconditions: NONE 
    */
    if(findItemJ(jury,*juryVotesList)!=NULLJ){//We check if the jury already exits
        printf("+ Error: Create not possible");
        return;
    }
    if (lastJ(*juryVotesList)==MAX_LIST-1){//We check if the list is full
        printf("+ Error: Create not possible");
        return;
    }
    tItemJ judge;
    strcmp(judge.juryName,jury);
    judge.totalVoters=totalVoters;
    if(insertItemJ(judge,juryVotesList)==true){//we check if it is added correctly
        printf("* Create: jury %s totalvoters %d",judge.juryName,judge.totalVoters);
        return;
    }
    printf("+ Error: Create not possible");
    return;
}

 

void addParticipant(char *juryName, char *tParticipantName, char *EUParticipant, tListJ *juryVotesList)
{
    tPosJ pos;
    pos=findItemJ(*juryName,*juryVotesList);
    if (findItemP(*tParticipantName)){

    }

}


   

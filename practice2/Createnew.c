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
        printf("+ Error: Create not possible\n");
        return;
    }
    if (lastJ(*juryVotesList)==MAX_LIST-1){//We check if the list is full
        printf("+ Error: Create not possible\n");
        return;
    }
    tItemJ judge;
    strcpy(judge.juryName,jury);
    judge.totalVoters=totalVoters;
    judge.participantList=NULLP;
    judge.nullVotes=0;
    judge.validVotes=0;
    if(insertItemJ(judge,juryVotesList)==true){//we check if it is added correctly
        printf("* Create: jury %s totalvoters %d\n",judge.juryName,judge.totalVoters);
        return;
    }
    printf("+ Error: Create not possible\n");
    return;
}

 

void addParticipant(char *juryName, char *ParticipantName, char *EUParticipant, tListJ *juryVotesList)
{
    /*
        Goal: Add participant to the jury 
        Input: jury name, participant name, if it is er or non-eu and the jury list
        Output: NONE
        Preconditions: jury's list is initialized, valid names and a valid eu value
        Postconditions: NONE 
    */
    if(isEmptyListJ(*juryVotesList)==true){//we check if there exits juries
        printf("+ Error: New not possible\n");
        return;
    }
    tPosJ pos;
    pos=findItemJ(juryName,*juryVotesList);//Look if the judge exit
    if (pos==NULLJ){
        printf("+ Error: New not possible\n");
        return;
    }
    tItemJ juri;
    juri=getItemJ(pos,*juryVotesList);

    bool emptylist=isEmptyListP(juri.participantList);
    if (!emptylist && findItemP(ParticipantName,juri.participantList)!=NULLP){
        printf("+ Error: New not possible\n");
        return;
    }

    tItemP temp;//I create the participant
    strcpy(temp.participantName,ParticipantName);
    temp.numVotes=0;
    temp.EUParticipant=false;
    if (strcmp(EUParticipant,"eu")==0)
        temp.EUParticipant=true;

    
    if(!insertItemP(temp,&juri.participantList)){
        printf("+ Error: New not possible\n");
        return;
    }
    printf("* New: jury %s participant %s location %s\n",juryName,temp.participantName,EUParticipant);
    if(emptylist)//if the list was empty we need to update the jury list
        updateItemJ(juri,pos,juryVotesList);
}

void disqualify(char *ParticipantName, tListJ *juryVotesList)
{
    /*
        Goal: Disqualify participants from all the jury of the list
        Input: Participant's name and jury list
        Output: NONE
        Preconditions: juries and participants lists are initialized
        Postconditions: If the participant exits, will be disqualify
    
    */
    
    //we check if the jury list is emtpy
    if(isEmptyListJ(*juryVotesList)){
        printf("+ Error: Disqualify not possible\n");
        return;
    }

    //we go through the list
    for (tPosJ pjury=firstJ(*juryVotesList);pjury!=NULLJ;pjury=nextJ(pjury,*juryVotesList)){
        
        tItemJ jury;
        jury=getItemJ(pjury,*juryVotesList);//we take the jury
        printf("Jury %s\n",jury.juryName);

        if(isEmptyListP(jury.participantList)){//if the participant list is empty
            printf("No participant %s\n\n",ParticipantName);
        }

        else{
            tPosP pdisparticipant;
            tItemP disparticipant;

            pdisparticipant=findItemP(ParticipantName,jury.participantList);//we search for the participant
            
            if(pdisparticipant==NULLP){//if participant doesn't exit
                printf("No participant %s\n\n",ParticipantName);
            }
            else{
                disparticipant=getItemP(pdisparticipant,jury.participantList);
                jury.nullVotes=jury.nullVotes+disparticipant.numVotes;
                jury.validVotes=jury.validVotes-disparticipant.numVotes;
                printf("Participant %s disqualified\n\n",disparticipant.participantName);
                deleteAtPositionP(pdisparticipant,&jury.participantList);
                updateItemJ(jury,pjury,juryVotesList);
                
            }
        }
    }

}
#include "mainFunctions.h"

void addContestant(tList* participants, char* participantName, char* EUParticipant)
{
    int itemInserted;
    //CREATE NODE
    tItemL tempconcursant;// this is my item
    strcpy(tempconcursant.participantName, participantName);//we add the parameters
    tempconcursant.numVotes=0;//we set votes to 0
    if (strcmp("eu",EUParticipant)==0)
        tempconcursant.EUParticipant=true;//we set the eu or non-eu
    else{
        tempconcursant.EUParticipant=false;
    }

    //ADD NODE TO LIST
    tPosL pos;
    pos = findItem(participantName,*participants);
    if (pos != LNULL){ //Contestant already exists
        printf("+ Error: New not possible\n");
        return;
    }

    
    itemInserted = insertItem(tempconcursant, LNULL, participants);//insert item in the last position
    if (!itemInserted){
        printf("+ Error: New not possible\n");
        return;
    }

    printf("* New: participant %s location ", participantName);
    if (tempconcursant.EUParticipant==true){
        printf("eu\n");
        return;
    }    
    printf("non-eu\n");
}

void disqualifyContestant (char* participantName, tList* participants, int* nullVotes, int* totalVotes)
{
    tPosL pos;
    tItemL contestant;
    //We serach for the constestant
    pos=findItem(participantName,*participants);

    if(pos==LNULL){//contestant does not exit
        printf("+Error: Disqualify not possible\n");
        return;
    }
    
    contestant=getItem(pos,*participants);
    printf("*Disqualify: participant %s location ", contestant.participantName);
    if (contestant.EUParticipant==true)
        printf("eu\n");
    else 
        printf("non.eu\n");
    
    //we set null it's votes
    *nullVotes+=contestant.numVotes;
    *totalVotes-=contestant.numVotes;
    
    deleteAtPosition(pos,participants);
}

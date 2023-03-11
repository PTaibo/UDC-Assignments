#include "mainFunctions.h"

void addContestant(tList* participants, char* participantName, char* EUParticipant)
{
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

    int itemInserted;
    
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

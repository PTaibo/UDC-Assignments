#include "mainFunctions.h"

void addContestant(tList* participants, char* participantName, char* EUParticipant)
{
    int pos;
    tItemL tempconcursant;// this is my item
    pos=findItem(*participantName,*participants);
    if (pos==LNULL){
        int temp,cor;
        strcpy(tempconcursant.participantName,*participantName);//we add the parameters
        tempconcursant.numVotes=0;//we set votes to 0
        if (strcmp("eu",EUParticipant==0))
            tempconcursant.EUParticipant=true;//we set the eu or non-eu
        else{
            tempconcursant.EUParticipant=false;
        }
        temp=last(*participants);//to the last position
        cor=insertItem(tempconcursant, temp, participants);//insert item in the last position
        if (cor==0)
            printf("+ Error: New not possible");
        else 
            printf("* New: participant %s location ",*participantName);
            if (tempconcursant.EUParticipant==true){
                printf("eu");
            }   
            else 
                printf("non-eu");
        }
    else {
        printf("+ Error: New not possible");
    }
}
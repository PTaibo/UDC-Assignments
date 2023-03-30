/*
 * TITLE: PROGRAMMING II LABS       SUBTITLE: Practical 1
 * AUTHOR 1: Siyuan He              LOGIN 1: siyuan.he
 * AUTHOR 2: Paula Taibo Suárez     LOGIN 2: p.taibo
 * GROUP: 6.1                       DATE: 16 / 03 / 23
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#define MAX_BUFFER 255

#ifdef DYNAMIC_LIST
#include "dynamic_list.h"
#endif
#ifdef STATIC_LIST
#include "static_list.h"
#endif

int EUstringToBool (char* str){
    if (!strcmp(str, "eu")){
        return 1;
    }

    return 0;
}

char* EUboolToString (int isEU){
    char* location;
    if (isEU){
        location = "eu";
    }
    else {
        location = "non-eu";
    }
    return location;
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

void addContestant(tList* participants, char* participantName, char* EUParticipant)
{
    //CREATE NODE
    tItemL tempconcursant;
    strcpy(tempconcursant.participantName, participantName);
    tempconcursant.numVotes=0;
    tempconcursant.EUParticipant = EUstringToBool(EUParticipant);

    //ADD NODE TO LIST

    //Check if the participant already exists
    tPosL pos;
    pos = findItem(participantName,*participants);
    if (pos != LNULL){
        printf("+ Error: New not possible\n");
        return;
    }

    //If it doesn't, insert it in the list
    int itemInserted;
    itemInserted = insertItem(tempconcursant, LNULL, participants);

    //Print information
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

void addVote (char* contestantName, tList* contestants, int* nullVotes, int* totalVotes)
{
    //Check if contestant exists
    tPosL participantPos = findItem(contestantName, *contestants);
    if (participantPos == LNULL){
        printf("+ Error: Vote not possible. Participant %s not found. NULLVOTE\n", contestantName);
        *nullVotes += 1;
        return;
    }

    //If it does, add the vote
    tItemL participant = getItem(participantPos, *contestants);
    participant.numVotes++;
    updateItem(participant, participantPos, contestants);
    *totalVotes += 1;

    //Print information
    printf("* Vote: participant %s location %s numvotes %d\n", contestantName,
                                                               EUboolToString(participant.EUParticipant),
                                                               participant.numVotes);
}

void printStats (tList* contestants, int* totalVotes, int* nullVotes, char* totalVoters)
{
    //Check if there are contestants
    if (isEmptyList(*contestants)){
        printf("+ Error: Stats not possible\n");
        return;
    }

    //Print participant's information
    for (tPosL it = first(*contestants); it != LNULL; it = next(it, *contestants)){
        tItemL participant = getItem(it, *contestants);
        printf("Participant %s location %s numvotes %d", participant.participantName,
                                                         EUboolToString(participant.EUParticipant),
                                                         participant.numVotes);
        if (!*totalVotes){ //If there are no votes [to avoid dividing by 0]
            printf(" (0.00%%)\n");
        }
        else {
            printf(" (%.2f%%)\n", (float)( (participant.numVotes*100) / *totalVotes) );
        }
    }

    //Print voter's information
    printf("Null votes %d\n", *nullVotes);
    printf("Participation: %d votes from %s voters ", *nullVotes + *totalVotes, totalVoters);
    if (!atoi(totalVoters)){ //Avoid dividing by 0
        printf("(0.00%%)\n");
    }
    else {
        printf("(%.2f%%)\n", (float)( (*nullVotes + *totalVotes)*100 / atoi(totalVoters) ));
    }
}

void processCommand(char *commandNumber, char command, char *param1, char *param2, tList* contestants, int* nullVotes, int* totalVotes) {
    //printf("Command: %s %c %s %s\n", commandNumber, command, param1, param2);
    //Print generic input information
    for (int i = 0; i < 20; i++)
        printf("*");
    printf("\n");
    printf("%s %c: ", commandNumber, command);

    switch (command) { //Specific input prints and command function call
        case 'N': //New
            printf("participant %s location %s\n", param1, param2);
            addContestant(contestants, param1, param2);
            break;
        case 'V': //Vote
            printf("participant %s\n", param1);
            addVote(param1, contestants, nullVotes, totalVotes);
            break;
        case 'D': //Disqualify
            printf("participant %s\n", param1);
            disqualifyContestant(param1, contestants, nullVotes, totalVotes);
            break;
        case 'S': //Stats
            printf("totalvoters %s\n", param1);
            printStats(contestants, totalVotes, nullVotes, param1);
            break;
        default:
            break;
    }
}

void readTasks(char *filename) {
    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    f = fopen(filename, "r");

    if (f != NULL) {
        //Variables that needed throughout the program
        tList contestants;
        createEmptyList(&contestants);
        int nullVotes = 0;
        int totalVotes = 0;

        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, &contestants, &nullVotes, &totalVotes);
        }

        //Frees all remaining allocated memory from the list
        while (!isEmptyList(contestants)){
            deleteAtPosition(first(contestants), &contestants);
        }
        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}


int main(int nargs, char **args) {

    char *file_name = "new.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
        #ifdef INPUT_FILE
        file_name = INPUT_FILE;
        #endif
    }

    readTasks(file_name);

    return 0;
}

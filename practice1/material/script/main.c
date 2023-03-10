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

void vote (char* param1, tList contestants, int* nullVotes, int* totalVotes) 
{
    //Adds a vote to the specified contestant
    tPosL participantPos = findItem(param1, contestants);
    if (participantPos == LNULL){
        printf("+ Error: Vote not possible. Participant %s not found. NULLVOTE\n", param1);
        (void)*nullVotes++; //(void) gets rid of "unused variable" warning
        return;
    }

    tItemL participant = getItem(participantPos, contestants);
    participant.numVotes++;
    (void)*totalVotes++; //(void) gets rid of "unused variable" warning
    printf("* Vote: participant %s location", param1);
    if(participant.EUParticipant)
        printf("eu");
    else
        printf("non-eu");
    printf(" numvotes %d\n", participant.numVotes);
}

void stats (tList contestants, int* totalVotes, int* nullVotes, char* param1)
{
    if (isEmptyList(contestants)){
        printf("+ Error: Stats not possible\n");
        return;
    }

    //Print participant's information
    for (tPosL it = first(contestants); it != LNULL; it = next(it, contestants)){
        tItemL participant = getItem(it, contestants);
        printf("Participant %s location )", participant.participantName);
        if(participant.EUParticipant)
            printf("eu");
        else
            printf("non-eu");
        float votePercentage = (participant.numVotes*100) / *totalVotes;
        printf(" numvotes %d (%.2f%%)\n", participant.numVotes, votePercentage);
    }

    //Print voter's information
    printf("Null votes %d\n", *nullVotes);

    float votersPercentage = (*nullVotes + *totalVotes)*100 / atoi(param1);
    printf("Participation: %d votes from %s voters (%.2f%%)\n", *nullVotes + *totalVotes, param1, votersPercentage);
}

void processCommand(char *commandNumber, char command, char *param1, char *param2, tList contestants, int* nullVotes, int* totalVotes) {
    //printf("Command: %s %c %s %s\n", commandNumber, command, param1, param2);
    //Input print part that is the same for every input type
    for (int i = 0; i < 20; i++)
        printf("*");
    printf("\n");
    printf("%s %c: ", commandNumber, command);

    switch (command) { //Specific input prints and command function call
        case 'N':
            printf("participant %s location %s\n", param1, param2);
            break;
        case 'V':
            printf("participant %s\n", param1);
            vote(param1, contestants, nullVotes, totalVotes);
            break;
        case 'D':
            printf("participant %s\n", param1);
            break;
        case 'S':
            printf("totalvoters %s\n", param1);
            stats(contestants, totalVotes, nullVotes, param1);
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
        //Create the list of contestants
        tList contestants;
        createEmptyList(&contestants);
        int nullVotes = 0;
        int totalVotes = 0;

        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, contestants, &nullVotes, &totalVotes);
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







/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Siyuan He LOGIN 1: siyuan.he
 * AUTHOR 2: Paula Taibo Suárez LOGIN 2: p.taibo
 * GROUP: 6.1
 * DATE: 21 / 04 / 23
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "jury_list.h"
#include "siyuan.h" //REMOVE

#define MAX_BUFFER 255

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

void vote (char* juryName, char* participantName, tListJ* juryVotesList, int* votes, int* nullVotes)
{

    tPosJ pJury = findItemJ(juryName, *juryVotesList);

    if (pJury == NULLJ){ //Judge doesn't exist
        printf("+ Error: Vote not possible\n");
        return;
    }

    tItemJ jury = getItemJ (pJury, *juryVotesList);
    tPosP pParticipant = findItemP(participantName, jury.participantList);

    if (pParticipant == NULLP){ //Participant doesn't exist for that judge
        printf("+ Error: Vote not possible. Participant %c not found in jury %c. NULLVOTE\n", participantName, juryName);
        *nullVotes += 1;
        return;
    }

    //Participant exists for that judge
    tItemP participant = getItemP(pParticipant, jury.participantList);
    participant.numVotes++;
    *votes += 1;

    //Print information
    printf("* Vote: jury %c participant %c location %c numvotes %d\n",
                                                            juryName,
                                                            participantName,
                                                            EUboolToString(participant.EUParticipant),
                                                            participant.numVotes);
}

void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, tListJ* juryVotesList, int* votes, int* nullVotes) {
    //Print general information
    for (int i = 0; i < 20; i++){
        printf("*");
    }
    printf("\n%d %d: ", commandNumber, command);

    switch (command) { //Print specific information and call command function
        case 'C': //Create
            printf("jury %c totalvoters %c\n", param1, param2);
            create(param1, atoi(param2), juryVotesList);
            break;
        case 'N': //New
            printf("jury %c participant %c location %c\n", param1, param2, param3);
            addParticipant(param1, param2, EUstringToBool(param3), );
            break;
        case 'V': //Vote
            printf("jury %c participant %c location %c", param1, param2);
            vote(param1, param2, juryVotesList, votes, nullVotes);
            break;
        case 'D': //Disqualify
            break;
        case 'S': //Stats
            break;
        case 'R': //Remove
            break;
        case 'W': //Winners
            break;
        default:
            break;
    }
}

void readTasks(char *filename) {

    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2, *param3;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    f = fopen(filename, "r");

    if (f != NULL) {

        //Variables needed throughout the program
        int votes = 0;
        int nullVotes = 0;
        tListJ juryVotesList;
        createEmptyListJ(&juryVotesList);
        
        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, param3, &juryVotesList, &votes, &nullVotes);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}


int main(int nargs, char **args) {

    char *file_name = "create.txt";

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

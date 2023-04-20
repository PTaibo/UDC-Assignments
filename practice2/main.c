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

typedef struct {
    char name[100];
    int votes;
    bool tie;
} winner;

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

void vote (char* juryName, char* participantName, tListJ* juryVotesList)
{
    /*
        Goal: increase the number of votes of a participant
        Input: name of the jury that votes, name of the voted participant, list of jurys, total votes and total null votes
        Output: NONE
        Preconditions: the jurys list is initialized
        Postconditions: if the jury and participant exist the participant's and total votes are increased. If only the jury exists, the total null votes are increased
    */

    tPosJ pJury = findItemJ(juryName, *juryVotesList);

    if (pJury == NULLJ){ //Judge doesn't exist
        printf("+ Error: Vote not possible\n");
        return;
    }

    tItemJ jury = getItemJ (pJury, *juryVotesList);
    tPosP pParticipant = findItemP(participantName, jury.participantList);

    if (pParticipant == NULLP){ //Participant doesn't exist for that judge
        printf("+ Error: Vote not possible. Participant %s not found in jury %s. NULLVOTE\n", participantName, juryName);
        jury.nullVotes++;

        updateItemJ(jury, pJury, juryVotesList);
        return;
    }

    //Participant exists for that judge
    tItemP participant = getItemP(pParticipant, jury.participantList);
    participant.numVotes += 1;
    jury.validVotes += 1;

    updateItemP(participant, pParticipant, &jury.participantList);
    updateItemJ(jury, pJury, juryVotesList);

    //Print information
    printf("* Vote: jury %s participant %s location %s numvotes %d\n",
                                                            juryName,
                                                            participantName,
                                                            EUboolToString(participant.EUParticipant),
                                                            participant.numVotes);
}

void stats(tListJ* juryVotesList)
{
    /*
        Goal: print the voting statistics
        Input: jurys list, total of votes and total of nullvotes
        Output: NONE
        Preconditions: jury's list is initialized
        Postconditions: NONE
    */

    if (isEmptyListJ(*juryVotesList)) { //If there are no jurys
        printf("+ Error: Stats not possible\n");
        return;
    }

    //For each jury in the list
    for (tPosJ pJury = firstJ(*juryVotesList); pJury != NULLJ; pJury = nextJ(pJury, *juryVotesList)){

        tItemJ jury = getItemJ(pJury, *juryVotesList);
        printf("Jury %s\n", jury.juryName);

        if (isEmptyListP(jury.participantList)){ //There are no participats
            printf("No participants\n");
        }
        else {
            //For every participant in that jury
            for (tPosP pParticipant = firstP(jury.participantList); pParticipant != NULLP; pParticipant = nextP(pParticipant, jury.participantList)){
                tItemP participant = getItemP(pParticipant, jury.participantList);

                printf("Participant %s location %s numvotes %d", participant.participantName,
                                                                EUboolToString(participant.EUParticipant),
                                                                participant.numVotes);
                if (!jury.validVotes){ //If there are no votes [to avoid dividing by 0]
                    printf(" (0.00%%)\n");
                }
                else {
                    printf(" (%.2f%%)\n", ((float)participant.numVotes*100.) / (float)jury.validVotes);
                }
            }
        }

        //Print jury's information
        printf("Nullvotes %d\n", jury.nullVotes);
        printf("Participation: %d votes from %d voters ", jury.validVotes + jury.nullVotes, jury.totalVoters);
        if (!jury.totalVoters){ //Avoid dividing by 0
            printf("(0.00%%)\n");
        }
        else {
            printf("(%.2f%%)\n", ((float)(jury.validVotes + jury.nullVotes)*100.) / (float)jury.totalVoters);
        }
        printf("\n"); //Blank line between the juries
    }
}

void removeJuries(tListJ* juryVotesList)
{
    /*
        Goal: removes juries with 0 valid votes
        Input: a list of juries
        Output: NONE
        Preconditions: the list is initialized
        Postconditions: all juries with 0 valid votes have been removed from the list
    */

    if (isEmptyListJ(*juryVotesList)){ //There are no juries
        printf("+ Error: Remove not possible\n");
        return;
    }

    bool removedJurys = false;
    for (tPosJ pJury = firstJ(*juryVotesList); pJury != NULLJ;){
        tItemJ jury = getItemJ(pJury, *juryVotesList);

        if (!jury.validVotes){
            printf("* Remove: jury %s\n", jury.juryName);
            deleteAtPositionJ(pJury, juryVotesList);
            removedJurys = true;
            continue;
        }

        pJury = nextJ(pJury, *juryVotesList);
    }

    if (!removedJurys){ //No juries were removed
        printf("+ Error: Remove not possible\n");
    }
}

void getWinners(tListJ* juryVotesList)
{
    if (isEmptyListJ(*juryVotesList)){ //There are no juries
        printf("+ Error: Winners is not possible\n");
        return;
    }

    for (tPosJ pJury = firstJ(*juryVotesList); pJury != NULLJ; pJury = nextJ(pJury, *juryVotesList)){
        tItemJ jury = getItemJ(pJury, *juryVotesList);
        printf("Jury %s\n", jury.juryName);

        if (isEmptyListP(jury.participantList)){ //There are no participants
            printf("Location eu: No winner\nLocation non-eu: No winner\n\n"); //Two new lines to get blank line before next jury
            break;
        }

        winner eu;
            eu.votes = -1;
            eu.tie = false;
        winner non_eu;
            non_eu.votes = -1;
            non_eu.tie = false;

        for (tPosP pParticipant = firstP(jury.participantList); pParticipant != NULLP; pParticipant = nextP(pParticipant, jury.participantList)){
            tItemP participant = getItemP(pParticipant, jury.participantList);

            //Eu participants
            if (participant.EUParticipant){
                if (participant.numVotes > eu.votes){ //Found a new max
                    strcpy(eu.name, participant.participantName);
                    eu.votes = participant.numVotes;
                    eu.tie = false;
                    continue;
                }

                if (participant.numVotes == eu.votes){ //Max is repeated
                    eu.tie = true;
                }
                continue;
            }

            //Non-eu participants
            if (participant.numVotes > non_eu.votes){ //Found a new max
                strcpy(non_eu.name, participant.participantName);
                non_eu.votes = participant.numVotes;
                non_eu.tie = false;
                continue;
            }

            if (participant.numVotes == non_eu.votes){ //Max is repeated
                non_eu.tie = true;
            }
        }

        printf("Location eu: ");
        if (eu.votes == -1 || eu.tie){ //There were no eu participants or there was a tie
            printf("No winner\n");
        }
        else {
            printf("Participant %s numvotes %d\n", eu.name, eu.votes);
        }

        printf("Location non-eu: ");
        if (non_eu.votes == -1 || non_eu.tie){ //There were no eu participants or there was a tie
            printf("No winner\n");
        }
        else {
            printf("Participant %s numvotes %d\n", non_eu.name, non_eu.votes);
        }

        printf("\n"); //Prints a blank line between the juries
    }
}

void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, tListJ* juryVotesList) {
    //Print general information
    for (int i = 0; i < 20; i++){
        printf("*");
    }
    printf("\n%s %c:", commandNumber, command);

    switch (command) { //Print specific information and call command function
        case 'C': //Create
            printf(" jury %s totalvoters %s\n", param1, param2);
            create(param1, atoi(param2), juryVotesList);
            break;
        case 'N': //New
            printf(" jury %s participant %s location %s\n", param1, param2, param3);
            addParticipant(param1, param2, param3, juryVotesList);
            break;
        case 'V': //Vote
            printf(" jury %s participant %s\n", param1, param2);
            vote(param1, param2, juryVotesList);
            break;
        case 'D': //Disqualify
            break;
        case 'S': //Stats
            printf("\n"); //There is nothing else to print
            stats(juryVotesList);
            break;
        case 'R': //Remove
            printf("\n"); //There is nothing else to print
            removeJuries(juryVotesList);
            break;
        case 'W': //Winners
            printf("\n"); //There is nothing else to print
            getWinners(juryVotesList);
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
        tListJ juryVotesList;
        createEmptyListJ(&juryVotesList);
        
        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, param3, &juryVotesList);
        }

        //Free all remaining memory
        for (tPosJ pJury = firstJ(juryVotesList); pJury != NULLJ; pJury = nextJ(pJury, juryVotesList)){
            tItemJ jury = getItemJ(pJury, juryVotesList);
            while (!isEmptyListP(jury.participantList)){
                deleteAtPositionP(firstP(jury.participantList), jury.participantList);
            }
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

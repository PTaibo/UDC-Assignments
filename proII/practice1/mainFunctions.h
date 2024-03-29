#ifndef MAIN_FUNCTIONS
#define MAIN_FUNCTIONS

#include <stdio.h>
#include <stdbool.h>
#include "dynamic_list.h"

void addContestant(tList* participants, char* participantName, char* EUParticipant);
void disqualifyContestant (char* participantName, tList* participants, int* nullVotes, int* totalVotes);

#endif

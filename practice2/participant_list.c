/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Paula Taibo Suárez LOGIN 1: p.taibo
 * AUTHOR 2: Siyuan He LOGIN 2: siyuan.he
 * GROUP: 6.1
 * DATE: 14 / 04 / 23
 */

#include "participant_list.h"
#define UNUSED __attribute__((unused)) //Gets rid of unused parameter warnings

bool createNode(tPosP *p)
{
    *p=malloc(sizeof(tNodeP));
    return *p!=NULLP;
}


void createEmptyListP (tListP* newList)
{
    *newList=NULLP;
}

bool isEmptyListP (tListP list)
{
    return list == NULLP;
}

tPosP firstP (tListP list)
{
    return list;
}

tPosP lastP (tListP list)
{
    tPosP p;
    for(p= list ; p->next != NULLP ; p= p->next);
    return p;
}

tPosP nextP (tPosP pos, UNUSED tListP list)
{
    return pos->next;
}

tPosP previousP (tPosP pos, tListP list)
{
    if (pos==list)
        return NULLP;
    tPosP p;
    for(p=list;p!=NULLP;p=p->next){
        if (p->next==pos)
            return p;
    }
    return NULLP;
}

bool insertItemP (tItemP item, tListP* list)
{
    //First create nodde
    tPosP temp;
    if (!(createNode(&temp)))//It is correctly created
        return 0;
    temp->next=NULLP;
    temp->participant=item;


    //The list is empty
    if (*list==NULLP){
        *list = temp;
        return 1;
    }



    tPosP pos = *list;

    //First position
    if (strcmp(pos->participant.participantName,item.participantName)>0){
        temp->next = *list;
        *list = temp;
        return 1;
    }

    //Middle position
    tPosP prev = *list;
    for (pos= pos->next; pos!=NULLP;prev = pos, pos=pos->next){
        if(strcmp(pos->participant.participantName,item.participantName)>0){
            temp->next = pos;
            prev->next = temp;
            return 1;
        }
    }
    //Last position
    prev->next = temp;
    return 1;
}


void deleteAtPositionP (tPosP pos, tListP* list)
{
    //Delete first element of the list
    if (pos==*list){
        *list= pos->next;
        free (pos);
        return;
    }
    //Delete at middle
    tPosP p;
    p=previousP(pos,*list);
    p->next=pos->next;
    free(pos);
    return;
}

tItemP getItemP (tPosP pos,UNUSED tListP list)
{
    return pos->participant;
}



void updateItemP (tItemP item, tPosP pos,UNUSED tListP* list)
{
    pos->participant=item;
}

tPosP findItemP (tParticipantName participant, tListP list)
{
    tPosP pos=list;
    if (strcmp(pos->participant.participantName,participant)>0){
        return NULLP;
    }
    for (pos=list; pos !=NULL; pos=pos->next){
        if ((strcmp(pos->participant.participantName,participant))==0)
            return pos;
    }
    return NULLP;
}
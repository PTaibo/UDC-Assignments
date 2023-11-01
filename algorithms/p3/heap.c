/*
TITLE: ALGORITHMS             SUBTITLE:P3
AUTHOR 1:PAULA TAIBO SUAREZ   LOGIN:P.TAIBO
AUTHOR 2:SIYUAN HE            LOGIN:SIYUAN.HE
GROUP:6.1                     DATE:23/10/2023
*/

#include "heap.h"


void initialize_heap(pheap h){

    if ((h = (struct heap *)malloc(sizeof(struct heap))) == NULL) {        
        return;
    }

}



void create_heap(int a[], int n, pheap h)
{

    initialize_heap(h);

    h->last=n-1;
    for (int i = 0; i < n; i++){
        h->vector[i]=a[i];
    }

}

int remove_min(pheap h)
{   
    //If the heap is empty
    if (h->last < 0){ 
        return -1;
    }

    //we keep the first one
    int min = h->vector[0];
    int pos = 0;

    //iterate through the list
    for (int i = 1; i <= h->last; i++){

        //we check if it is smaller
        if (h->vector[i] < min){//we check
            min = h->vector[i];
            pos = i;//we keep the position
        }

    }

    //we delete it from the list
    for (int i = pos; i < h->last; i++){
        h->vector[i] = h-> vector [i+1];
    }

    h->last--;

    return min;

}

void heap_sort (int a[], int n)
{
    pheap h = (struct heap *)malloc(sizeof(struct heap));

    create_heap (a, n, h);
    for (int i = 0; i < n; i++){
        a[i] = remove_min(h);
    }
    
}
/*
TITLE: ALGORITHMS             SUBTITLE:P3
AUTHOR 1:PAULA TAIBO SUAREZ   LOGIN:P.TAIBO
AUTHOR 2:SIYUAN HE            LOGIN:SIYUAN.HE
GROUP:6.1                     DATE:23/10/2023
*/

#include "heap.h"
#include <stdbool.h>
#include <stdio.h>

/*void initialize_heap(pheap h)
{
    h->last=0;
}

bool isEmptyHeap(pheap h)
{
    return h->last=0;
}

order(pheap h)

bool insertH(int a, pheap h)
{
    if (h->last=SZ){
        return 0;
    }
    else{
        h->last += 1;
        h->vector[h->last] = a;
        order();
    }
    

}

void create_heap(int a[], int n, pheap h)
{
    bool insert=true;

    initialize_heap(h);

    for (int i = 0; i < n, insert != false; i++){
        insert=insertH(a[i],h);
    }
    
    if(!insert){
        printf("Heap created incorrectly");
    }

}*/

void create_heap(int a[], int n, pheap h)
{
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

    int min = h->vector[0];//we start in the first
    int pos = 0;

    //iterate through the list
    for (int i = 1; i <= h->last; i++){

        if (h->vector[i] < min){//we check
            min = h->vectorj;
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

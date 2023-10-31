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

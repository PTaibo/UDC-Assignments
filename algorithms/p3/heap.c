/*
TITLE: ALGORITHMS             SUBTITLE:P3
AUTHOR 1:PAULA TAIBO SUAREZ   LOGIN:P.TAIBO
AUTHOR 2:SIYUAN HE            LOGIN:SIYUAN.HE
GROUP:6.1                     DATE:23/10/2023
*/

#include "heap.h"


/*bool initialize_heap(pheap h){

    if ((h = (struct heap *)malloc(sizeof(struct heap))) == NULL) {        
        return 0;
    }

    return 1;
}*/

void swap (pheap h, int j, int i)
{

    int tmp = h->vector[j];
    h->vector[j] = h->vector[i];
    h->vector[i] = tmp;
}


void PercolateDown(pheap h, int i)
{
    int leftChild, rightChild, j;

    do{
        leftChild = 2 * i + 1;
        rightChild = 2 * i + 2;
        j = i;

        if ((leftChild < h->last+1) && (h->vector[leftChild] < h->vector[i])){
            i = leftChild;
        }
        if ((rightChild < h->last+1) && (h->vector[rightChild] < h->vector[i])){
            i = rightChild;
        }
        
        swap (h, j, i);

    }while (j != i);
}


void create_heap(int a[], int n, pheap h)
{
    /*if (!initialize_heap(h)){
        printf("The array was not correctly created");
        return;
    }*/

    h->last=n-1;
    for (int i = 0; i < n; i++){
        //printf("Is %d ",a[1]);
        h->vector[i] = a[i];
    }
   
    for (int i = (h->last)/2 + 1; i >= 0; i--){
        PercolateDown(h,i);
    }

    //free(h);
}

int remove_min(pheap h)
{   
    int min;
    //If the heap is empty
    min = h->vector[0];
    if (h->last < 1){
        if (h->last < 0){
            return -1;
        } 
        else{
            h->last--;
            return min;
        }
    }

    h->vector[0] = h->vector[h->last];
    h->last--;
    if (h->last > 0){
        PercolateDown(h,0);
    }

    return min;
}

void heap_sort (int a[], int n)
{
    pheap h;
    h = malloc(sizeof(struct heap));

    create_heap (a, n, h);

    for (int i = 0; i < n; i++){
        a[i] = remove_min(h);
    }
    free(h);
}
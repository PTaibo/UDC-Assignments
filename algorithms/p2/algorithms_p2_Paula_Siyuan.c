/*
TITLE: ALGORITHMS             SUBTITLE:P2
AUTHOR 1:PAULA TAIBO SUAREZ   LOGIN:P.TAIBO
AUTHOR 2:SIYUAN HE            LOGIN:SIYUAN.HE
GROUP:6.1                     DATE:09/10/2023
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#define k 1000



//sorting functions

void ins_sort (int v [], int n)
{
    int x, j;

    for (int i = 1; i < n; i++){
        x = v [i];
        j = i - 1;;

        while (j >= 0 && v[j] > x){
            v[j + 1] = v[j];
            j = j - 1;
        }

        v [j + 1] = x;
    }

}

void shell_sort (int v [], int n)
{
    int increment = n - 1;
    int j = 0;
    bool keepgoing;

    do{
        increment = increment / 2;

        for (int i = increment + 1; i < n; i++){
            int tmp = v[i];
            j = i;
            keepgoing = true;

            while (( (j - increment) > 0 ) && keepgoing){

                if (tmp < v[j - increment]){
                    v[j] = v[j-increment];
                    j = j - increment;
                }

                else 
                    keepgoing = false; 
                
            }

            v[j] = tmp;
        
        }        
    } 
    while (increment >= 1);
}

void init_seed()
{
    srand(time(NULL));
    /* set the seed of a new sequence of pseudo-random integers */
}


void random_init(int v [], int n)
{
    int i, m=2*n+1;
    for (i=0; i < n; i++)
        v[i] = (rand() % m) - n;
    /* generate pseudo-random numbers between -n and +n */
}

void print_array(int v[], int n)
{
    printf("[");
    for (int i = 0; i < n ; i++)
        printf(" %2d",v[i]);
    printf("]\n");
}

int isSorted (int arrayToCheck[], int arraySize)
{
    int prev = arrayToCheck[0];

    for (int i = 1; i < arraySize; i++){
        if (arrayToCheck[i] < prev){
            return 0;
        }
    }

    return 1;
}

void copyArray (int size, int src[], int dest[])
{
    for (int i = 0; i < size; i++){
        dest[i] = src[i];
    }
}

void checkAlgorithms(int arrayToOrder[], int arraySize)
{
    print_array(arrayToOrder, arraySize);
    printf("Sorted? %d\n", isSorted(arrayToOrder, arraySize) ? 1 : 0);

    printf("Insertion sort\n");
    print_array(arrayToOrder, arraySize);
    ins_sort(arrayToOrder, arraySize);
    printf("Sorted? %d\n", isSorted(arrayToOrder, arraySize) ? 1 : 0);

    printf("Shell sort\n");
    shell_sort(arrayToOrder, arraySize);
    print_array(arrayToOrder, arraySize);
    printf("Sorted? %d\n", isSorted(arrayToOrder, arraySize) ? 1 : 0);
}

void test ()
{
    printf("Random initialization\n");

    const int arraySize = 15;
    int unorderedArray[arraySize];
    random_init(unorderedArray, arraySize);

    checkAlgorithms(unorderedArray, arraySize);

    printf("Descending initialization\n");

    int descendingArray[arraySize];
    for (int i = arraySize; i > 0; i--){
        descendingArray[arraySize - i] = i;
    }

    checkAlgorithms(descendingArray, arraySize);
}
    
int main()
{
    init_seed();
    //test();
    int v[5]={3,2,1,0,4};
    shell_sort(v,5);
    print_array(v,5);
    
    return 0;
}


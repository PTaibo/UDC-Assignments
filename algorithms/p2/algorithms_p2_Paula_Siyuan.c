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

        while (j > 0 && v[j] > x){
            v[j + 1] = v[j];
            j = j - 1;
        }

        v [j + 1] = x;;
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
    while (increment > 0);
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

    
}
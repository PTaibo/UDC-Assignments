/*
TITLE: ALGORITHMS             SUBTITLE:P3
AUTHOR 1:PAULA TAIBO SUAREZ   LOGIN:P.TAIBO
AUTHOR 2:SIYUAN HE            LOGIN:SIYUAN.HE
GROUP:6.1                     DATE:23/10/2023
*/

#include <stdio.h>
#include "heap.h"
#include "test.h"
#define K 1000
#define N 32000



double microseconds() { /* obtains the system time in microseconds */
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;

    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void PrintLinealValues(int i,double v)
{
    double t,t08,t1,t12;

    t=v;
    double j= (double) i; //pow needs doubles
    t08=t/pow(j,0.8);
    t1=t/i;
    t12=t/pow(j,1.2);

    //printing results
    printf("%5d\t",i);
    printf("%7lf\t",t);
    printf("%lf\t",t08);
    printf("%lf\t\t",t1);
    printf("%lf\t\t",t12);
    printf("\n");
}


void printLinealTitle(){

   printf("   n\t  t(n)\t\tt(n)/n^0.8\tt(n)/n\t\tt(n)/n^1.2\n");

}

void time_createHeap()
{
    printf("\nCreate heap:\n");
    printLinealTitle();


    double timev = 0;
    double ta, tb, tCreateA, tCreateB;


    for (int i=500; i <= N; i = i*2){
        int v[i];
        pheap h;//no entiendo porque no puedo usar una funcion 
        h = (struct heap *)malloc(sizeof(struct heap));//why not check
        /*if ((h = (struct heap *)malloc(sizeof(struct heap))) == NULL) {        
            return; 
        }*/
        
        random_init(v,i);
        ta=microseconds();
        create_heap(v,i,h);
        tb=microseconds();
        timev=tb-ta;

        if (timev < 500){ //confidence threshold
            printf("*");
            ta=microseconds();

            for (int count = 0; count < K; count++){
                random_init(v,i);
                create_heap(v,i,h);
            }
            tb=microseconds();

            tCreateA = microseconds();

            for (int count = 0; count < K; count++){
                random_init(v,i);
            }

            tCreateB = microseconds();

            timev=((tb-ta)-(tCreateA-tCreateB))/K;
        }

        PrintLinealValues(i,timev);
        free(h);
    }

}



int main(){

    init_seed();
    test_create();    
    time_createHeap();
    return 0;
}

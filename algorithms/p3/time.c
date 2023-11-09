/*
TITLE: ALGORITHMS             SUBTITLE:P2
AUTHOR 1:PAULA TAIBO SUAREZ   LOGIN:P.TAIBO
AUTHOR 2:SIYUAN HE            LOGIN:SIYUAN.HE
GROUP:6.1                     DATE:09/10/2023
*/



#include "time.h"



double microseconds() { /* obtains the system time in microseconds */
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;

    return (t.tv_usec + t.tv_sec * 1000000.0);
}


void printLinealTitle(){

   printf("   n\t   t(n)\t\tt(n)/n^0.8\tt(n)/n\t\t       t(n)/n^1.2\n");

}

void printlogTitles(){

    printf(" n\t   t(n)\t\tt(n)/n^1\tt(n)/n*logn\t        t(n)/n^1.5\n");

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

void PrintlogValues(int i,double v)
{
    double t,t08,t1,t12;

    t=v;
    double j= (double) i; //pow needs doubles
    t08=t/pow(j,1);
    t1=t/(j*log(j));
    //t1=t/pow(j,1.3);
    t12=t/pow(j,1.5);

    //printing results
    printf("%5d\t",i);
    printf("%7lf\t",t);
    printf("%lf\t",t08);
    printf("%lf\t\t",t1);
    printf("%lf\t\t",t12);
    printf("\n");
}

void time_createHeap()
{
    printf("\nCreate heap:\n");
    printLinealTitle();


    double timev = 0;
    double ta, tb, tCreateA, tCreateB;


    for (int i=500; i <= N; i = i*2){
        int v[i];
        pheap h;
        h = malloc(sizeof(struct heap));
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

void time_ascendOrder(){
    printf("\nSort for ascending ordered array:\n");
    printlogTitles();

    double timev = 0;
    double ta, tb, tCreateA, tCreateB;


    for (int i=500; i <= N; i = i*2){
        int v[i];
        /*if ((h = (struct heap *)malloc(sizeof(struct heap))) == NULL) {        
            return; 
        }*/
        
        ascending_order_init(v,i);
        ta=microseconds();
        heap_sort(v,i);
        tb=microseconds();
        timev=tb-ta;

        if (timev < 500){ //confidence threshold
            printf("*");
            ta=microseconds();

            for (int count = 0; count < K; count++){
                ascending_order_init(v,i);
                heap_sort(v,i);
            }
            tb=microseconds();

            tCreateA = microseconds();

            for (int count = 0; count < K; count++){
                ascending_order_init(v,i);
            }

            tCreateB = microseconds();

            timev=((tb-ta)-(tCreateA-tCreateB))/K;
        }
        
        PrintlogValues(i, timev);
    }
}

void time_descendOrder(){
    printf("\nSort for descendig ordered array:\n");
    printlogTitles();

    double timev = 0;
    double ta, tb, tCreateA, tCreateB;


    for (int i=500; i <= N; i = i*2){
        int v[i];
        /*if ((h = (struct heap *)malloc(sizeof(struct heap))) == NULL) {        
            return; 
        }*/
        
        descending_order_init(v,i);
        ta=microseconds();
        heap_sort(v,i);
        tb=microseconds();
        timev=tb-ta;

        if (timev < 500){ //confidence threshold
            printf("*");
            ta=microseconds();

            for (int count = 0; count < K; count++){
                descending_order_init(v,i);
                heap_sort(v,i);
            }
            tb=microseconds();

            tCreateA = microseconds();

            for (int count = 0; count < K; count++){
                descending_order_init(v,i);
            }

            tCreateB = microseconds();

            timev=((tb-ta)-(tCreateA-tCreateB))/K;
        }
        
        PrintlogValues(i,timev);
    }
}

void time_randomOrder(){
    printf("\nSort for random array:\n");
    printlogTitles();

    double timev = 0;
    double ta, tb, tCreateA, tCreateB;


    for (int i=500; i <= N; i = i*2){
        int v[i];
        /*if ((h = (struct heap *)malloc(sizeof(struct heap))) == NULL) {        
            return; 
        }*/
        
        random_init(v,i);
        ta=microseconds();
        heap_sort(v,i);
        tb=microseconds();
        timev=tb-ta;

        if (timev < 500){ //confidence threshold
            printf("*");
            ta=microseconds();

            for (int count = 0; count < K; count++){
                random_init(v,i);
                heap_sort(v,i);
            }
            tb=microseconds();

            tCreateA = microseconds();

            for (int count = 0; count < K; count++){
                random_init(v,i);
            }

            tCreateB = microseconds();

            timev=((tb-ta)-(tCreateA-tCreateB))/K;
        }
        
        PrintlogValues(i,timev);
    }
}

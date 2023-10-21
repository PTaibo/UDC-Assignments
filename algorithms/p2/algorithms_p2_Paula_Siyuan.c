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
#define K 1000



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
    int increment = n;
    int j = 0;
    bool keepgoing;

    do{
        increment = increment / 2;

        for (int i = increment; i < n; i++){
            int tmp = v[i];
            j = i;
            keepgoing = true;

            while (( (j - increment) >= 0 ) && keepgoing){

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

//                      For computing time

double microseconds() { /* obtains the system time in microseconds */
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;

    return (t.tv_usec + t.tv_sec * 1000000.0);
}

//                      Creating arrays

void ascending_order_init(int v [], int n)
{
    for (int i = 0; i < n; i++){
        v[i] = i+1;
    }
}

void descending_order_init (int v [], int n)
{
    for (int i = n; i > 0; i--){
        v[n - i] = i;
    }
}

void copyArray (int size, int src[], int dest[])
{
    for (int i = 0; i < size; i++){
        dest[i] = src[i];
    }
}

//              Printing arrays

void print_array(int v[], int n)
{
    printf("[");
    for (int i = 0; i < n ; i++)
        printf(" %2d",v[i]);
    printf("]\n");
}

//Cheking sorts methods

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

void checkAlgorithms(int arrayToOrder[], int arraySize)
{
    print_array(arrayToOrder, arraySize);
    printf("Sorted? %d\n", isSorted(arrayToOrder, arraySize) ? 1 : 0);

    int cpyOfArray[arraySize];
    copyArray(arraySize, arrayToOrder, cpyOfArray);

    printf("Insertion sort\n");
    ins_sort(cpyOfArray, arraySize);
    print_array(cpyOfArray, arraySize);
    printf("Sorted? %d\n", isSorted(cpyOfArray, arraySize) ? 1 : 0);

    printf("Shell sort\n");
    shell_sort(arrayToOrder, arraySize);
    print_array(arrayToOrder, arraySize);
    printf("Sorted? %d\n", isSorted(arrayToOrder, arraySize) ? 1 : 0);
    printf("\n");
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
    descending_order_init(descendingArray, arraySize);

    checkAlgorithms(descendingArray, arraySize);
}

//              Printing the values

void PrintCuadraticValues(int i,double timev)
{
    double t,t18,t2,t22;

    t=timev;
    double j = (double) i; //pow needs type doubles
    t18=t/pow(j,1.8);
    t2=t/pow(j,2);
    t22=t/pow(j,2.2);
    
    //printing results
    printf("%5d\t",i);
    printf("%7lf\t",t);
    printf("%lf\t",t18);
    printf("%lf\t\t",t2);
    printf("%lf\t\t",t22);
    printf("\n");
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

void PrintShellValues(int i,double v)
{
    double t,t08,t1,t12;

    t=v;
    double j= (double) i; //pow needs doubles
    t08=t/pow(j,0.8);
    t1=t/pow(j,1.1);
    t12=t/pow(j,1.4);

    //printing results
    printf("%5d\t",i);
    printf("%7lf\t",t);
    printf("%lf\t",t08);
    printf("%lf\t\t",t1);
    printf("%lf\t\t",t12);
    printf("\n");
}


void printCuadraticTitle(){

    printf(" n\t  t(n)\t\tt(n)/n^1.8\tt(n)/n^2\t\tt(n)/n^2.2");

}

void printLinealTitle(){

   printf("   n\t  t(n)\t\tt(n)/n^0.8\tt(n)/n\t\tt(n)/n^1.2");

}

void printshellTitles(){

    printf(" n\t  t(n)\t\tt(n)/n^0.8\tt(n)/n^1.1\t\tt(n)/n^1.4");

}


//                  Calculating time for insertion sort

void asc_timeA()
{
    printf("\nInsertion sort for ascending ordered array:\n");
    printLinealTitle();
    printf("\n");

    double timev=0;
    double ta,tb,tCreateA,tCreateB;


    for (int i=500; i<=32000; i=i*2){
        int v[i];

        ascending_order_init(v,i);
        ta=microseconds();
        ins_sort(v, i);
        tb=microseconds();
        timev=tb-ta;

        if (timev < 500){ //confidence threshold
            printf("*");
            ta=microseconds();

            for (int count=0;count<K;count++){
                ascending_order_init(v,i);
                ins_sort(v,i);
            }
            tb=microseconds();

            tCreateA = microseconds();

            for (int count=0;count<K;count++){
                ascending_order_init(v,i);
            }

            tCreateB = microseconds();

            timev=((tb-ta)-(tCreateA-tCreateB))/K;
        }

        PrintLinealValues(i,timev);
    }
}

void desc_timeA()
{
    printf("\nInsertion sort for descending ordered array:\n");
    printCuadraticTitle();
    printf("\n");

    double timev=0;
    double ta,tb,tCreateA,tCreateB;


    for (int i=500; i<=32000; i=i*2){
        int v[i];

        descending_order_init(v,i);
        ta=microseconds();
        ins_sort(v, i);
        tb=microseconds();
        timev=tb-ta;

        if (timev < 500){ //confidence threshold
            printf("*");
            ta=microseconds();

            for (int count=0;count<K;count++){
                descending_order_init(v,i);
                ins_sort(v,i);
            }
            tb=microseconds();

            tCreateA = microseconds();

            for (int count=0;count<K;count++){
                descending_order_init(v,i);
            }

            tCreateB = microseconds();

            timev=((tb-ta)-(tCreateA-tCreateB))/K;
        }

        PrintCuadraticValues(i,timev);
    }
}

void random_timeA()
{
    printf("\nInsertion sort for random array:\n");
    printCuadraticTitle();
    printf("\n");

    double timev=0;
    double ta,tb,tCreateA,tCreateB;


    for (int i=500; i<=32000; i=i*2){
        int v[i];

        random_init(v,i);
        ta=microseconds();
        ins_sort(v, i);
        tb=microseconds();
        timev=tb-ta;

        if (timev < 500){ //confidence threshold
            printf("*");
            ta=microseconds();

            for (int count=0;count<K;count++){
                random_init(v,i);
                ins_sort(v,i);
            }
            tb=microseconds();

            tCreateA = microseconds();

            for (int count=0;count<K;count++){
                random_init(v,i);
            }

            tCreateB = microseconds();

            timev=((tb-ta)-(tCreateA-tCreateB))/K;
        }

        PrintCuadraticValues(i,timev);
    }
}


//          Calculating time for shell sort

void asc_timeB()
{
    printf("\nShell sort for ascending ordered array:\n");
    printshellTitles();
    printf("\n");

    double timev=0;
    double ta,tb,tCreateA,tCreateB;

    for (int i=500; i<=32000; i=i*2){ //for each n value 
        int v[i];

        ascending_order_init(v,i);
        ta=microseconds();
        shell_sort(v, i);
        tb=microseconds();
        timev=tb-ta;

            if(timev < 500){ //confidence threshold
                printf("*");
                ta=microseconds();

                for (int count=0;count<K;count++){
                    ascending_order_init(v,i);
                    shell_sort(v,i);
                }
                tb=microseconds();

                tCreateA = microseconds();
                for (int count=0;count<K;count++){
                    ascending_order_init(v,i);
                }
                tCreateB = microseconds();

                timev=((tb-ta)-(tCreateA-tCreateB))/K;

            }

        PrintShellValues(i,timev);
    }        

}


void desc_timeB()
{
    printf("\nShell sort for descending ordered array:\n");
    printshellTitles();
    printf("\n");

    double timev=0;
    double ta,tb,tCreateA,tCreateB;

    for (int i=500; i<=32000; i=i*2){ //for each n value 
        int v[i];

        descending_order_init(v,i);
        ta=microseconds();
        shell_sort(v, i);
        tb=microseconds();
        timev=tb-ta;

            if(timev < 500){ //confidence threshold
                printf("*");
                ta=microseconds();

                for (int count=0;count<K;count++){
                    descending_order_init(v,i);
                    shell_sort(v,i);
                }
                tb=microseconds();

                tCreateA = microseconds();
                for (int count=0;count<K;count++){
                    descending_order_init(v,i);
                }
                tCreateB = microseconds();

                timev=((tb-ta)-(tCreateA-tCreateB))/K;

            }

        PrintShellValues(i,timev);
    }  

}


void random_timeB()
{
    printf("\nShell sort for random array:\n");
    printshellTitles(); 
    printf("\n");

    double timev=0;
    double ta,tb,tCreateA,tCreateB;

    for (int i=500; i<=32000; i=i*2){ //for each n value 
        int v[i];

        random_init(v,i);
        ta=microseconds();
        shell_sort(v, i);
        tb=microseconds();
        timev=tb-ta;

            if(timev < 500){ //confidence threshold
                printf("*");
                ta=microseconds();

                for (int count=0;count<K;count++){
                    random_init(v,i);
                    shell_sort(v,i);
                }
                tb=microseconds();

                tCreateA = microseconds();
                for (int count=0;count<K;count++){
                    random_init(v,i);
                }
                tCreateB = microseconds();

                timev=((tb-ta)-(tCreateA-tCreateB))/K;

            }

        PrintShellValues(i,timev);
    }  

}




int main()

{

    init_seed();
    test();

    //insertion sort
    asc_timeA();
    desc_timeA();
    random_timeA();

    //shell sort
    asc_timeB();
    desc_timeB();
    random_timeB();
    
    //For test
    /*for (int i=0; i < 1; i++){

        test();

        //insertion sort
        asc_timeA();
        desc_timeA();
        random_timeA();

        //shell sort
        asc_timeB();
        desc_timeB();
        random_timeB();
    }*/


    return 0;
}


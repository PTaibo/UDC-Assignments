/*
TITLE: ALGORITHMS             SUBTITLE:P1
AUTHOR 1:PAULA TAIBO SUAREZ   LOGIN:P.TAIBO
AUTHOR 2:SIYUAN HE            LOGIN:SIYUAN.HE
GROUP:6.1                     DATE:03/02/2023
*/




#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#define k 1000


int maxSubSum1(int v[], int n)
{
    int i, j;
    long thisSum, maxSum = 0;
    
    for (i = 0; i < n; i++){
        thisSum = 0;

        for (j = i; j < n; j++){
            thisSum += v[j];

            if (thisSum > maxSum){
                maxSum = thisSum;
            }
        }
    }

    return maxSum;
}


int maxSubSum2(int v[], int n)
{
    long thisSum=0, maxSum=0;

    for (int i=0;i<n;i++){
        thisSum=thisSum+v[i];

        if (thisSum > maxSum) {
            maxSum=thisSum;
        }

        else if (thisSum<0){
            thisSum=0;
        }
    }

    return maxSum;
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
    printf("]");
}


void test1()
{
    printf("\nTEST 1:\n");
    printf("%25s%10s%15s\n", "", "maxSubSum1", "maxSubSum2");

    int a=0, b=0;
    int v[30]={-9,2,-5,-4,6,4,0,9,2,5,-2,-1,-9,-7,//given data
                -1,9,-2,1,-7,-8,15,-2,-5,-4,16,7,-5,6,7,-7};
    int v2[5];

    for (int i=1; i<=30; i++){
        printf(" %2d",v[i-1]);

        if (i % 5 == 0 && i != 0){

            //we take each 5 numbers during loop for compute
            for (int j=0,temp=i-1;j<5;j++,temp--){
                v2[j]=v[temp];
            }

            a = maxSubSum1(v2, 5);
            b = maxSubSum2(v2, 5);
            printf("%15d%15d\n", a, b);
        }
    }
}


void test2()
{
    int i, a, b;
    int v[9];

    //printing titles
    printf("\nTEST 2:\n");
    printf("%33s%15s%15s\n", "", "  maxSubSum1", "  maxSubSum2");

    for (i = 0; i < 10; i++)
    {
        random_init(v, 9);
        print_array(v, 9);
        a = maxSubSum1(v, 9);
        b = maxSubSum2(v, 9);
        printf("%15d%15d\n", a, b);
    }
}


double microseconds() { /* obtains the system time in microseconds */
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;

    return (t.tv_usec + t.tv_sec * 1000000.0);
}


void printvaluesa(int i,double timev)
{
    double t,t18,t2,t22;

    t=timev;
    double j = (double) i; //pow needs type doubles
    t18=t/pow(j,1.6);
    t2=t/pow(j,2);
    t22=t/pow(j,2.3);
    
    //printing results
    printf("%5d\t",i);
    printf("%7lf\t",t);
    printf("%lf\t",t18);
    printf("%lf\t\t",t2);
    printf("%lf\t\t",t22);
    printf("\n");
}


void timeA()
{
    printf("\nSubMax1:\n");
    printf("   n\t  t(n)\t\tt(n)/n^1.8\tt(n)/n^2\t\tt(n)/n^2.2");
    printf("\n");

    double timev=0;
    double ta,tb;

    //each value of n is a multiple of 2 
    for (int i=500; i<=32000; i=i*2){
        int v[i];

        random_init(v,i);
        ta=microseconds();
        maxSubSum1(v, i);
        tb=microseconds();
        timev=tb-ta;

        if (timev < 500){ //confidence threshold
            ta=microseconds();

            for (int count=0;count<k;count++){
                maxSubSum1(v,i);
            }
            
            tb=microseconds();
            timev=(tb-ta)/k;
        }

        printvaluesa(i,timev);
    }
}


void printvaluesb(int i,double v)
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


void timeB()
{
    printf("\nSubMax2:\n");
    printf("   n\t  t(n)\t\tt(n)/n^0.8\tt(n)/n\t\t       t(n)/n^1.2");
    printf("\n");

    double timev=0;
    double ta,tb;

    for (int i=500; i<=32000; i=i*2){ //for each n value 
        int v[i];

        random_init(v,i);
        ta=microseconds();
        maxSubSum2(v, i);
        tb=microseconds();
        timev=tb-ta;

            if(timev < 500){ //confidence threshold
                ta=microseconds();

                for (int count=0;count<k;count++){
                    maxSubSum2(v,i);
                }

                tb=microseconds();
                timev=(tb-ta)/k;
            }

        printvaluesb(i,timev);
    }  

}


int main()
{
    /*
    //for testing
    for (int i=0;i<4;i++){ 
        init_seed();
        timeA();
        timeB();
    }
    */
    
    init_seed();
    test1();
    test2();
    timeA();
    timeB();
    
    return 0;
    
}
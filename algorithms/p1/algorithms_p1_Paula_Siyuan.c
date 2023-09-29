#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#define k 1000
#define MAX_N 7


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
    srand(time(NULL)); /* set the seed of a new sequence of pseudo-random integers */
}

void random_init(int v [], int n)
{
    int i, m=2*n+1;
    for (i=0; i < n; i++)
        v[i] = (rand() % m) - n; /* generate pseudo-random numbers between -n and +n */
}

void print_array(int v[], int n)
{
    printf("[");
    for (int i = 0; i < n ; i++)
        printf(" %02d",v[i]);
    printf("]");
}

void test1()
{
    printf("\nTEST 1:\n");
    int a=0, b=0;
    int v[30]={-9,2,-5,-4,6,4,0,9,2,5,-2,-1,-9,-7,
                -1,9,-2,1,-7,-8,15,-2,-5,-4,16,7,-5,6,7,-7};
    int v2[5];
    printf("%25s%10s%15s\n", "", "maxSubSum1", "maxSubSum2");
    for (int i=1;i<=30;i++){
        printf(" %02d",v[i-1]);
        if (i % 5 == 0 && i != 0){
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

double microsegundos() { /* obtiene la hora del sistema en microsegundos */
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void timeA()
{
    printf("SubMax1:\n");
    print_titlesa();
    printf("\n");
    double timev[MAX_N]={0};
    double ta,tb,t=0;
    for (int i=500,h=0; i<=32000, h<7; i=i*2,h++){
        int v[i];
        random_init(v,i);
        ta=microsegundos();
        maxSubSum1(v, i);
        tb=microsegundos();
        timev[h]=tb-ta;
        if(timev[h] < 500){
            ta=microsegundos();

            for (int count=0;count<k;count++){
                maxSubSum1(v,i);
            }

            tb=microsegundos();
            timev[h]=(tb-ta)/k;
        }
        
        printvaluesa(i,h,timev);
}
}

void timeB()
{
    printf("\nSubMax2:\n");
    print_titlesb();
    printf("\n");
    double timev[MAX_N]={0};
    double ta,tb,t=0;
    for (int i=500,h=0; i<=32000,h<7; i=i*2,h++){
        int v[i];
        random_init(v,i);
        ta=microsegundos();
        maxSubSum1(v, i);
        tb=microsegundos();
        timev[h]=tb-ta;
            if(timev[h] < 500){
                ta=microsegundos();

                for (int count=0;count<k;count++){
                    maxSubSum2(v,i);
                }

                tb=microsegundos();
                timev[h]=(tb-ta)/k;
            }

            printvaluesb(i,h,timev);
    }  

}

void print_titlesa()
{
    printf("n\tt(n)\t\tt(n)/n^1.8\tt(n)n^2\t\t\tt(n)/n^2.2");
}

void print_titlesb()
{
    printf("n\tt(n)\t\tt(n)/n^0.8\tt(n)n\t\t\tt(n)/n^1.2");
}

void printvaluesa(int i,int h,double v[])
{
    double t,t18,t2,t22;
    printf("%d\t",i);
    t=v[h];
    printf("%lf\t",t);
    t18=t/pow(i,1.6);
    printf("%lf\t",t18);
    t2=t/pow(i,2);
    printf("%lf\t\t",t2);
    t22=t/pow(i,2.3);
    printf("%lf\t\t",t22);
    printf("\n");
}

void printvaluesb(int i,int h,double v[])
{
    double t,t08,t1,t12;
    printf("%d\t",i);
    t=v[h];
    printf("%lf\t",t);
    t08=t/pow(i,0.8);
    printf("%lf\t",t08);
    t1=t/i;
    printf("%lf\t\t",t1);
    t12=t/pow(i,1.2);
    printf("%lf\t\t",t12);
    printf("\n");
}

int main()
{
    
    //for (int i=0;i<3;i++){
        init_seed();
        //test1();
        //test2();
        //timeA();
        timeB();
        
    //
    return 0;
    
}
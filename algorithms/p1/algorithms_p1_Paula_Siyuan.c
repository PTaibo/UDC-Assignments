#include <stdio.h>



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
    int a=0, b=0;
    int v[30]={-9,2,-5,-4,6,4,0,9,2,5,-2,-1,-9,-7,-1,9,-2,1,-7,-8,15,-2,-5,-4,16,7,-5,6,7,-7};
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
    printf("test\n");
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

int main()
{
    init_seed();
    test1();
    //test2();
    return 0;
}

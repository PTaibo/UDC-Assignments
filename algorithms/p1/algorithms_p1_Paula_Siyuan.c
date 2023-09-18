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

void print_array(int v[], int n)
{
    /* ... */
}

void test1()
{
    /* ... */
}

void test2()
{
    int i, a, b;
    int v[9];
    printf("test\n");
    printf("%33s%15s%15s\n", "", "maxSubSum1", "maxSubSum2");
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
    test2();
    return 0;
}

#include "test.h"
#define size 20

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

void copy_array(int a[], int b[],int sz)
{

    for (int i = 0 ; i < sz; i++){
        b[i] = a[i];
    }

}

void print_array(int v[], int n)
{
    printf("[");
    for (int i = 0; i < n ; i++)
        printf(" %2d",v[i]);
    printf("]\n");
}

int check_heapVector (pheap h)
{
    int n = h->last;

    if (n < 1){
        return 1;
    }

    for (int i = 0; i <= n; i++){

        int leftchild = 2 * i + 1;
        int rightchild = 2 * i + 2; 

        if (leftchild > n || rightchild > n){
            continue;
        }

        if ((h->vector[i] > h->vector[leftchild])){
            return 0;
        }

        if (h->vector[i] > h->vector[rightchild]){
            return 0;        
        }

    }

    return 1;
}

void print_heap (pheap h)
{
    printf("[");
    for (int i = 0; i <= h->last; i++){
        printf(" %2d",h->vector[i]);
    }
    printf("]\n");
}

void check_array(int a[], int sz)
{
    pheap h;
    h = malloc(sizeof(struct heap));

    create_heap(a, sz, h);
    printf("This is the heap vector:\n");
    print_heap(h);
    printf("sorted? %d\n",check_heapVector(h));
    remove_min(h);
    print_heap(h);
    printf("sorted? %d",check_heapVector(h));
    free(h);
}

void test_create ()
{

    printf("Random array\n");

    int array[size];
    
    for (int i = 0; i < 5; i++){
        //we print the array
        random_init(array, size);
        printf("This is the array:\n");
        print_array(array, size);
        printf("\n");

        //now we check it
        check_array(array, size);
        printf("\n---------------------------\n");
    }
}

int check_minarray(int a[], int n)
{
    if (n < 1){
        return 1;
    }

    for (int i = 1; i < n; i++){
        if (a[i-1] > a[i]){
            return 0;
        }
    }

    return 1;
}

void check_heapsort()
{
    const int sizes = 20;
    int a[sizes];
    random_init(a, sizes);
    print_array(a ,sizes);
    heap_sort(a, sizes);
    print_array(a, sizes);
    printf("ordered? %d",check_minarray(a, sizes));
}
#include "test.h"

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

void copy_array(int a[], int b[],int size)
{

    for (int i = 0 ; i < size; i++){
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

void check_array(int a[], int size)
{
    pheap h;
    h = (struct heap *)malloc(sizeof(struct heap));

    create_heap(a, size, h);
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

    const int size = 20;
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

/*
 * TITLE: ALGORITHMS                SUBTITLE: P4
 * AUTHOR 1: PAULA TAIBO SUÁREZ     LOGIN: P.TAIBO
 * AUTHOR 2: SIYUAN HE              LOGIN: SIYUAN.HE
 * GROUP: 6.1                       DATE: 09/10/2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include <sys/time.h>

#define MAX_SIZE 1000
#define K 1000

typedef int **matrix;

int minimindistance (matrix distances, int *unvisited, int n, int sz){

    int minIndex = -1;
    int minValue = INT_MAX;

    for (int i = 0; i < sz; i++) {
        if (unvisited[i] && distances[n][i] < minValue) {
            minValue = distances[n][i];
            minIndex = i;
        }
    }

    return minIndex;
}

void printmatrix (matrix distances, int n){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            printf("%d ",distances[i][j]);
        }
        printf("\n");
    }
}


void dijkstra(matrix graph, matrix distances, int sz)
{
    int n, v = 0;
    int *unvisited = malloc(sz * sizeof(int));
    for (n = 0; n < sz; n++)
    {
        //we copy graph to distance
        for (int i = 0; i < sz; i++)
        {
            unvisited[i] = 1; //we set our unviseted 
            distances[n][i] = graph[n][i];
        }
        unvisited[n] = 0;

        for (int i = 0; i <= sz - 2; i++){

            //we got the node with the miminum distance in Distance[n][v]
            v = minimindistance(distances, unvisited, n, sz);
            unvisited[v] = 0;

            //we check for the rest of the unvisited 
            for (int j = 0; j < sz; j++) {
                if (unvisited[j] && distances[n][j] > distances[n][v] + graph[v][j]) {
                    distances[n][j] = distances[n][v] + graph[v][j];
                }   
            }

        }
    }
    free(unvisited);
}

matrix createMatrix (int n)
{
    matrix aux = malloc(n*sizeof(int*));
    if (aux == NULL)
        return NULL;
    for (int i = 0; i < n; i++){
        aux[i] = malloc(n*sizeof(int));
        if (aux[i] == NULL)
            return NULL;
    }
    return aux;
}

void freeMatrix (matrix m, int n)
{
    for (int i = 0; i < n; i++)
        free(m[i]);
    free(m);
}

void initMatrix (int data[], int n, matrix m)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++){
            m[i][j] = data[i*n + j];
        }
}

int compare (int correct[], int n, matrix ans)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j< n; j++)
            if (ans[i][j] != correct[i*n + j])
                return 0;
    return 1;
}

void test_dijkstra (int n, int data[], int correct[])
{
    matrix graph = createMatrix(n);
    matrix distances = createMatrix(n);
    initMatrix(data, n, graph);
    dijkstra(graph, distances, n);
    printmatrix(distances,n);
    printf("Distances are %s\n",
            compare(correct, n, distances) == 1 ?
                "correct" :
                "wrong");
}

void test1 ()
{
    int data[25] = {0, 1, 8, 4, 7,
                    1, 0, 2, 6, 5,
                    8, 2, 0, 9, 5,
                    4, 6, 9, 0, 3,
                    7, 5, 5, 3, 0};
    int correct[25] = {0, 1, 3, 4, 6,
                       1, 0, 2, 5, 5,
                       3, 2, 0, 7, 5,
                       4, 5, 7, 0, 3,
                       6, 5, 5, 3, 0};
    test_dijkstra(5, data, correct);
}

void test2 ()
{
    int data[16] = {0, 1, 4, 7,
                    1, 0, 2, 8,
                    4, 2, 0, 3,
                    7, 8, 3, 0};
    int correct[16] = {0, 1, 3, 6,
                       1, 0, 2, 5,
                       3, 2, 0, 3,
                       6, 5, 3, 0};
    test_dijkstra(4, data, correct);
}

void init_seed()
{
    srand(time(NULL));
    /* set the seed of a new sequence of pseudo-random integers */
}

void randomInit(int n, matrix m)
{
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            m[i][j] = rand() % MAX_SIZE + 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= i; j++)
            if (i == j)
                m[i][j] = 0;
            else
                m[i][j] = m[j][i];
}

double microseconds() { /* obtains the system time in microseconds */
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;

    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void printlogTitles(){

    printf(" n\t   t(n)\t\tt(n)/n^1\tt(n)/n*logn\t        t(n)/n^1.4\n");

}

void PrintlogValues(int i, double v)
{
    double t,t08,t1,t12;

    t=v;
    double j= (double) i; //pow needs doubles
    t08=t/pow(j,2);
    //t1=t/(j + )*log(j));
    t1=t/pow(j,2.7);
    t12=t/pow(j,3.2);

    //printing results
    printf("%5d\t",i);
    printf("%7lf\t",t);
    printf("%lf\t",t08);
    printf("%lf\t\t",t1);
    printf("%lf\t\t",t12);
    printf("\n");
}

void get_complexity()
{
    printf("Dijkstra execution time:\n");
    printlogTitles();

    double timev = 0, ta, tb;

    for (int i = 5; i <= 320; i = i*2){
        matrix m, d;
        m = createMatrix(i);
        d = createMatrix(i);
        randomInit(i, m);
        if (m )
        ta = microseconds();
        dijkstra(m, d, i);
        tb = microseconds();
        timev = tb - ta;

        if (timev < 500) { // Confidence threshold
            printf("*");

            ta = microseconds();
            for (int cnt = 0; cnt < K; cnt++){
                randomInit(i, m);
                dijkstra(m, d, i);
            }
            tb = microseconds();
            
            double tCreateA = microseconds();

            for (int cnt = 0; cnt < K; cnt++){
                randomInit(i,m);
            }

            double tCreateB = microseconds();

            timev = ((tb - ta) - (tCreateA - tCreateB)) / K;
        }

        PrintlogValues(i, timev);
    }
}

int main(){
    init_seed();
    //test1();
    //test2();
    get_complexity();
}
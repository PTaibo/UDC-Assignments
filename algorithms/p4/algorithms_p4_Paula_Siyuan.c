#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define MAX_SIZE 1000

typedef int **matrix;

int minimindistance (int *distances, int *unvisited, int n){

    int minIndex = -1;
    int minValue = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (unvisited[i] && distances[i] < minValue) {
            minValue = distances[i];
            minIndex = i;
        }
    }

    return minIndex;
}


void dijkstra(matrix graph, matrix distances, int sz)
{
    int n, min, v = 0;
    int *unvisited = malloc(sz * sizeof(int));
    for (n = 0; n < sz; n++)
    {
        for (int i = 0; i < sz; i++)
        {
            unvisited[i] = 1;
            distances[n][i] = graph[n][i];
        }
        unvisited[n] = 0;

        for (int i = 0; i < n -2; i++){
            int v = minimindistance(distances[n], unvisited, n);

            unvisited[v] = 0;

             for (int j = 0; j < n; j++) {
                if (unvisited[j] && Distances[n][j] > Distancesn[n][j] + M[v][j]) {
                    Distances[n][j] = Distances[n][v] + M[v][j];
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



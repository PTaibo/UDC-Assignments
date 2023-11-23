#include <stdio.h>

typedef int **matrix;


void dijkstra(matrix graph, matrix distances, int sz)
{
    int n, i, j, min, v = 0;
    int *unvisited = malloc(sz * sizeof(int));
    for (n = 0; n < sz; n++)
    {
        for (i = 0; i < sz; i++)
        {
            unvisited[i] = 1;
            distances[n][i] = graph[n][i];
        }
        unvisited[n] = 0;
        /*
        ...
        */
    }
    free(unvisited);
}

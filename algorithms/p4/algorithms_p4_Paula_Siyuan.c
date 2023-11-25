#include <stdio.h>

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

/*
TITLE: ALGORITHMS             SUBTITLE:P3
AUTHOR 1:PAULA TAIBO SUAREZ   LOGIN:P.TAIBO
AUTHOR 2:SIYUAN HE            LOGIN:SIYUAN.HE
GROUP:6.1                     DATE:23/10/2023
*/

#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define SZ 256000

struct heap{
    int last;
    int vector[SZ];
};

typedef struct heap *pheap;



void create_heap(int a[], int n, pheap h);
int remove_min(pheap h);
void heap_sort(int a[], int n);
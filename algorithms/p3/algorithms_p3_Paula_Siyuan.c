/*
TITLE: ALGORITHMS             SUBTITLE:P3
AUTHOR 1:PAULA TAIBO SUAREZ   LOGIN:P.TAIBO
AUTHOR 2:SIYUAN HE            LOGIN:SIYUAN.HE
GROUP:6.1                     DATE:23/10/2023
*/

#include <stdio.h>
#include "heap.h"
#include "test.h"
#include "time.h"




int main()
{
    init_seed();
    test_create();    
    time_createHeap();
    check_heapsort();
    time_ascendOrder();
    time_descendOrder();
    return 0;
}

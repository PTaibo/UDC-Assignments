/*
TITLE: ALGORITHMS             SUBTITLE:P2
AUTHOR 1:PAULA TAIBO SUAREZ   LOGIN:P.TAIBO
AUTHOR 2:SIYUAN HE            LOGIN:SIYUAN.HE
GROUP:6.1                     DATE:09/10/2023
*/
#include <stdio.h>
#include <stdbool.h>



//sorting functions

void ins_sort (int v [], int n)
{
    int x, j;

    for (int i = 1; i < n; i++){
        x = v [i];
        j = i - 1;;

        while (j > 0 && v[j] > x){
            v[j + 1] = v[j];
            j = j - 1;
        }

        v [j + 1] = x;;
    }

}

void shell_sort (int v [], int n)
{
    int increment = n - 1;
    int j = 0;
    bool keepgoing;

    do{
        increment = increment / 2;

        for (int i = increment + 1; i < n; i++){
            int tmp = v[i];
            j = i;
            keepgoing = true;

            while (( (j - increment) > 0 ) && keepgoing){

                if (tmp < v[j - increment]){
                    v[j] = v[j-increment];
                    j = j - increment;
                }

                else 
                    keepgoing = false; 
                
            }

            v[j] = tmp;
        
        }        
    } 
    while (increment > 0);
    
}
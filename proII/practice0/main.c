/*
TITLE: PROGRAMMING II LABS	SUBTITLE: P0
AUTHOR 1: SIYUAN HE 		LOGIN: SIYUAN.HE
AUTHOR 2: PAULA TAIBO SUAREZ	LOGIN: P.TAIBO
GROUP: 6.1			DATE: 03/02/2023
*/

#include <stdio.h>
//#include "rational_pointer.h"
#include "rational_struct.h"
int main(){
    Rational r1, r2, r3, r4, s;
    r1= createRational(2,3);
    r2= createRational(5,7);
    r3= createRational(7,3);
    r4= createRational(5,4);
    s=sum(r1,r2);
    printf("The sum is %d/%d\n",numerator(s),denominator(s));
    s=sum(r3,r4);
    printf("The sum is %d/%d\n",numerator(s),denominator(s));
    return 0;
}

/*
TITLE: PROGRAMMING II LABS      SUBTITLE: P0
AUTHOR 1: SIYUAN HE             LOGIN: SIYUAN.HE
AUTHOR 2: PAULA TAIBO SUAREZ    LOGIN: P.TAIBO 
GROUP: 6.1                      DATE: 03/02/2023
*/

#ifndef RATIONAL_RATIONAL_POINTER_H
#define RATIONAL_RATIONAL_POINTER_H


typedef struct Data* Rational;
struct Data {
    int num;
    int den;
};
Rational createRational(int n,int d);
int numerator(Rational r);
int denominator(Rational r);
Rational sum(Rational r1, Rational r2);

#endif

/*
TITLE: PROGRAMMING II LABS      SUBTITLE: P0
AUTHOR 1: SIYUAN HE             LOGIN: SIYUAN.HE
AUTHOR 2: PAULA TAIBO SUAREZ    LOGIN: P.TAIBO 
GROUP: 6.1                      DATE: 03/02/2023
*/

#include "rational_struct.h"

Rational createRational(int n, int d){
    Rational temp;
    temp.num = n;
    temp.den = d;
    return temp;
}

int numerator(Rational r){
    return r.num;
}

int denominator(Rational r){
    return r.den;
}

Rational sum(Rational r1, Rational r2){
    Rational s;
    s.num = r1.num * r2.den + r2.num * r1.den;
    s.den = r1.den * r2.den;
    return s;
}

#include "rational_pointer.h"
//Opertaion to create a rational number
Rational createRational(int n,int d){
    Rational temp;
    temp= malloc(sizeof(*temp));
    temp->num=n;
    temp->den=d;
    return temp;
}
//Opereration that returns the numerator of a rational number
int numerator(Rational r){
    return r->num;
}

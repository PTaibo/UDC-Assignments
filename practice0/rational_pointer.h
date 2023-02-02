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
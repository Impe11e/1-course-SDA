#include <stdio.h>

typedef struct {
    double prevF;
    double sum;
} Struct;

double teylor(double x, unsigned int n, unsigned int i, Struct *str) {
    if (i > n) return 0;

    teylor(x, n, i + 1, str);

    double F;
    unsigned int j = n - i + 1;

    if (j == 1) {
        F = x - 1;
    } else {
        F = -str->prevF * (x - 1) * (j - 1) / j;
    }

    str->prevF = F;
    str->sum += F;

    if(i==1){
    return str->sum;}
}

int main() {
    double x, res;
    unsigned int n;

    printf("enter x: ");
    scanf("%lf", &x);
    printf("enter n: ");
    scanf("%u", &n);

    Struct str = {0, 0};

    res = teylor(x, n, 1, &str);
    printf("Result: %lf\n", res);
}































#include <stdio.h>

double teylor(double x, unsigned int n, unsigned int i, double F, double sum) {
    if (i > n) return sum;
    if (i == 1) F = x - 1;

    sum += F;
    F = -F * (x - 1) * i / (i + 1);

    return teylor(x, n, i + 1, F, sum);
}

int main() {
    double x, res;
    unsigned int n;

    printf("enter x: ");
    scanf("%lf", &x);
    printf("enter n: ");
    scanf("%u", &n);

    res = teylor(x, n, 1, 0, 0);
    printf("Result: %lf\n", res);
}
//spusk

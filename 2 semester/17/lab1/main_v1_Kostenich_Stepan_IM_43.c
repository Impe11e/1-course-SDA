#include <stdio.h>

double sumSinhV1Series(double x, unsigned int n, unsigned int i, double fi, double sum) {
    double result = -1;

    if (i >= n) {
        result = sum;
    } else {
        fi *= x * x / (4.0 * i * i + 2.0 * i);
        sum += fi;
        result = sumSinhV1Series(x, n, i + 1, fi, sum);
    }

    return result;
}

double sinhV1(double x, unsigned int n) {
    const unsigned int i = 1;
    const double fi = x;
    const double sum = 0.0;

    return x + sumSinhV1Series(x, n, i, fi, sum);
}

int main() {
    double x;
    unsigned int n;

    printf("Enter x (|x| < 10^6):");
    scanf("%lf", &x);
    printf("Enter n:");
    scanf("%u", &n);

    printf("\nThe result is %.15lf\n", sinhV1(x, n));

    return 0;
}

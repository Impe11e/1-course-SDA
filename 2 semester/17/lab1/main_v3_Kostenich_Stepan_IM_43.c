#include <math.h>
#include <stdio.h>

double sumSinhV3Series(double x, unsigned int n, unsigned int i, double fi) {
    double result = -1;

    if (i >= n) {
        result = 0.0;
    } else {
        fi *= x * x / (4.0 * i * i + 2.0 * i);
        result = sumSinhV3Series(x, n, i + 1, fi);
        result += fi;
    }

    return result;
}

double sinhV3(double x, unsigned int n) {
    const unsigned int i = 1;
    const double fi = x;

    return x + sumSinhV3Series(x, n, i, fi);
}

int main() {
    double x;
    unsigned int n;

    printf("Enter x (|x| < 10^6):");
    scanf("%lf", &x);
    printf("Enter n:");
    scanf("%u", &n);

    printf("\nThe result is %.15lf\n", sinhV3(x, n));

    return 0;
}

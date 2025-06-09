#include <stdio.h>

typedef struct {
    double fi;
    double sum;
} Result;

Result sumSinhV2Series(double x, unsigned int n) {
    Result result;

    if (n <= 1) {
        result = (Result) {x, x};
    } else {
        Result prev = sumSinhV2Series(x, --n);
        result.fi = prev.fi * (x * x / (4.0 * n * n + 2.0 * n));
        result.sum = prev.sum + result.fi;
    }

    return result;
}

double sinhV2(double x, unsigned int n) {
    return sumSinhV2Series(x, n).sum;
}

int main() {
    double x;
    unsigned int n;

    printf("Enter x (|x| < 10^6):");
    scanf("%lf", &x);
    printf("Enter n:");
    scanf("%u", &n);

    printf("\nThe result is %.15lf\n", sinhV2(x, n));

    return 0;
}

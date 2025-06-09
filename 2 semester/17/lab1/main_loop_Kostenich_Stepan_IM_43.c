#include <stdio.h>

double sinhLoop(double x, unsigned int n) {
    double result = 0.0;
    double fi = x;

    for (int i = 1; i < n; i++) {
        fi *= x * x / (4.0 * i * i + 2.0 * i);
        result += fi;
    }

    return result + x;
}

int main() {
    double x;
    unsigned int n;

    printf("Enter x (|x| < 10^6):");
    scanf("%lf", &x);
    printf("Enter n:");
    scanf("%u", &n);

    printf("\nThe result is %.15lf\n", sinhLoop(x, n));

    return 0;
}

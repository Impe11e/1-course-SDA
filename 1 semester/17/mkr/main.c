#include <stdio.h>
#include <tgmath.h>

double ApproximatePower(double a, double x, const int n) {
    if (a == 0) {
        return x == 0 ? NAN : 0.0;
    }

    double sum = 1.0;
    double pow = 1.0;
    double factorial = 1.0;

    const double term = x * log(a);

    for(int i = 1; i<=n; i++) {
        pow *= term;
        factorial *= i;

        sum += pow / factorial;
    }

    return sum;
}

int main() {
    double a, x;
    int n;

    printf("Enter a, x, n:\n");
    scanf("%lf %lf %d", &a, &x, &n);

    printf("The result is %lf", ApproximatePower(a, x, n));

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double sum;
    double F;
} Result;

double sum1(int n, double x, int i, double F, double sum) {
    if (x < 1 && x > -1) {
        sum += F;
        printf("F%d = %lf, sum = %lf\n", i, F, sum);

        if (i == n) {
            return sum;
        }

        return sum1(n, x, i + 1, F * (x * x * (2 * i - 1)) / (2 * i + 1), sum);
    }
    return sum;
}

Result sum2(int n, double x, int i) {
    Result result;

    if (x < 1 && x > -1) {
        if (i == 1) {
            result.F = x;
            result.sum = x;
            printf("F%d = %lf, sum = %lf\n", i, result.F, result.sum);
            return result;
        }

        Result prev = sum2(n, x, i - 1);
        result.F = prev.F * (x * x * (2 * i - 3)) / (2 * i - 1);
        result.sum = prev.sum + result.F;
        printf("F%d = %lf, sum = %lf\n", i, result.F, result.sum);

        return result;
    }

    return result;
}

double sum3(int n, double x, int i, double F) {
    if (x < 1 && x > -1) {
        if (i == n) {
            printf("F%d = %lf, sum = %lf\n", i, F, F);
            return F;
        }

        double sum = sum3(n, x, i + 1, F * (x * x * (2 * i - 1)) / (2 * i + 1));
        sum += F;

        printf("F%d = %lf, sum = %lf\n", i, F, sum);
        return sum;
    }
    return 0;
}

double loops(int n, double x, int i, double F, double sum) {
    if (x < 1 && x > -1) {
        for(int i = 1; i <= n; i++) {
            sum += F;
            printf("F%d = %lf, sum = %lf\n", i, F, sum);
            F *= (x * x * (2 * i - 1)) / (2 * i + 1);
        }
        return sum;
    }
    return sum;
}

int main() {
    int n = 5;
    int i = 1;
    double x = -0.6;
    double F = x;

    printf("=== First method ===\n");
    double result1 = sum1(n, x, i, F, 0);
    printf("Result: %lf\n\n", result1);

    printf("=== Second method ===\n");
    double result2 = sum2(n, x, n).sum;
    printf("Result: %lf\n\n", result2);

    printf("=== Third method ===\n");
    double result3 = sum3(n, x, i, F);
    printf("Result: %lf\n\n", result3);

    printf("=== Loops ===\n");
    double result_loops = loops(n, x, i, F, 0);
    printf("Result: %lf\n\n", result_loops);

    return 0;
}

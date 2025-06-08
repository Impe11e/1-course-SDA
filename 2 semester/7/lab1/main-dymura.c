#include <stdio.h>

typedef struct {
    double last_calculated_value;
    double sum;
} Result;

Result calculate_sum_tail_recursion(const int n, const double x) {
    Result calcData = {0, 0};

    double res;

    if (n == 1) {
        res = (x - 1) / (x + 1);
    } else {
        calcData = calculate_sum_tail_recursion(n - 1, x);

        res = calcData.last_calculated_value * ((2 * n - 1) * (x - 1) * (x - 1)) / (
                  (2 * n + 1) * (2 * n + 1) * (x + 1) * (x + 1));
    }


    return (Result){
        .sum = calcData.sum + res,
        .last_calculated_value = res
    };
}

void sum_tail_recursion(const int n, const double x) {
    const double res = calculate_sum_tail_recursion(n, x).sum;
    printf("sum_tail_recursion: %lf\n", res);
}

double calculate_sum_head_recursion(const int n, const int i, const double x, const double prev) {
    if (i > n) return 0;

    double res = 0;

    if (i == 1) {
        res = (x - 1) / (x + 1);
    } else {
        res = prev * ((2 * i - 1) * (x - 1) * (x - 1)) / ((2 * i + 1) * (2 * i + 1) * (x + 1) * (x + 1));
    }

    return res + calculate_sum_head_recursion(n, i + 1, x, res);
}


void sum_head_recursion(const int n, const double x) {
    const double res = calculate_sum_head_recursion(n, 1, x, x);
    printf("sum_head_recursion: %lf\n", res);
}


double calculate_sum_recursive_combined(const int n, const int i, const double x, const double prev) {
    if (i > n) {
        return prev;
    }

    double val;
    if (i == 1) {
        val = (x - 1) / (x + 1);
    } else {
        val = prev * ((2 * i - 1) * (x - 1) * (x - 1)) / ((2 * i + 1) * (2 * i + 1) * (x + 1) * (x + 1));
    }

    double res = calculate_sum_recursive_combined(n, i + 1, x, val);
    res += prev;

    return res;
}

void sum_recursive_combined(const int n, const double x) {
    const double res = calculate_sum_recursive_combined(n, 1, x, 0);
    printf("sum_recursive_combined: %lf\n", res);
}

// циклiчний варiант рiшення задачi
double sum_iterative(const int n, const double x) {
    double Fi = (x - 1) / (x + 1);

    double sum = Fi;

    for (int i = 2; i <= n; i++) {
        Fi = Fi * ((2 * i - 1) * (x - 1) * (x - 1)) / ((2 * i + 1) * (2 * i + 1) * (x + 1) * (x + 1));
        sum += Fi;
    }

    return sum;
}

int main() {
    int n;
    double x;

    printf("Enter the value for n: ");
    scanf("%d", &n);

    printf("Enter the value for x (x > 0): ");
    scanf("%lf", &x);

    sum_tail_recursion(n, x);
    sum_head_recursion(n, x);
    sum_recursive_combined(n, x);

    printf("sum_iterative: %lf\n", sum_iterative(n, x));

    return 0;
}

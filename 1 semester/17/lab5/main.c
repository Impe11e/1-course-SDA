#include <stdio.h>

const int m = 8, n = 10;

double matrix[8][10] =
{
    {9.94,  9.80,  0.12,  5.00,  9.75,  9.98,  8.96,  9.31,  9.48,  5.00},
    {9.55,  9.80, -0.35,  5.00,  9.64,  9.91,  7.71,  8.06,  0.78,  4.27},
    {8.00,  4.25, -0.62,  5.00,  8.87,  9.19,  6.25,  7.77, -0.26,  3.79},
    {6.69,  4.25, -1.83, -0.01,  5.29,  7.20,  5.41,  6.67, -4.99,  3.01},
    {4.33,  4.25, -3.05, -0.02, -1.94,  6.89,  1.18,  6.26, -4.99,  2.68},
    {3.19, -1.40, -4.83, -0.04, -3.34,  6.87,  1.18,  5.36, -5.67,  2.13},
    {1.62, -1.40, -6.58, -2.28, -7.78,  5.14,  1.18,  1.99, -8.27,  1.05},
    {1.37, -1.40, -8.73, -3.87, -8.73,  0.89,  1.18, -5.90, -9.13,  0.00},
};

void PrintMatrix() {
    printf("\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%5.2lf ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void SearchAlgorithm1() {
    for (int i = 0; i < n; i++) {
        int L = 0, R = m - 1;
        int j;
        double x;

        while (L <= R) {
            j = (L + R) / 2;
            x = matrix[j][i];

            if (x > 5) {
                L = j + 1;
            } else if (x < 0) {
                R = j - 1;
            } else {
                break;
            }
        }

        if (x <= 5 && x >= 0) {
            printf("Found element within range [0, 5] in column %d: (%d, %d) %5.2lf\n", i, j, i, x);
        } else {
            printf("No element was found within range [0, 5] in column %d\n", i);
        }
    }
}

int main(void) {
    PrintMatrix();
    SearchAlgorithm1();

    return 0;
}
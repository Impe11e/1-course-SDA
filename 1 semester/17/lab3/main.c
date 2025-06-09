#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double RandomRange(const double min, const double max) {
    return min + rand() / (RAND_MAX / (max - min));
}

void FillRandom(const int n, double matrix[][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = RandomRange(-100.0, 100.0);
        }
    }
}

void PrintMatrix(const int n, double matrix[][n]) {
    printf("\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%7.3lf ", matrix[i][j]);
        }
        printf("\n");
    }
}

void PrintSkewDiagonal(const int n, double matrix[][n]) {
    printf("\nSkew diagonal:\n");

    for (int i = 0; i < n; i++) {
        printf("%7.3lf ", matrix[n - i - 1][i]);
    }
    printf("\n");
}

void DoTask(const int n, double matrix[][n]) {
    int posI = -1;
    int negI = -1;

    for (int i = 0; i < n; i++) {
        double e = matrix[n - i - 1][i];

        if (posI == -1 && e > 0) posI = i;
        if (e < 0) negI = i;
    }

    double posVal = posI == -1 ? -1 : matrix[n - posI - 1][posI];
    double negVal = negI == -1 ? -1 : matrix[n - negI - 1][negI];

    printf("\nFirst positive = %.3lf\n", posVal);
    printf("Last negative = %.3lf\n", negVal);

    if (posI != -1 && negI != -1) {
        matrix[n - posI - 1][posI] = negVal;
        matrix[n - negI - 1][negI] = posVal;
    } else {
        printf("\nEither the first positive or the last negative element was not found.\n");
    }
}

void ChangeSkewDiagonal(const int n, double matrix[][n]) {
    printf("\nDo you wanna change the skew diagonal? (1, 0)\n");

    int choice;
    scanf("%d", &choice);
    if (choice == 1) {
        for (int i = 0; i < n; i++) {
            scanf("%lf", &matrix[n - i - 1][i]);
        }
    }
}

int main(void) {
    srand(time(nullptr));
    int n;

    printf("\nEnter the size of the square matrix: \n");
    scanf("%d", &n);
    double matrix[n][n];

    FillRandom(n, matrix);
    PrintMatrix(n, matrix);
    PrintSkewDiagonal(n, matrix);

    ChangeSkewDiagonal(n, matrix);
    PrintMatrix(n, matrix);
    PrintSkewDiagonal(n, matrix);

    DoTask(n, matrix);
    PrintMatrix(n, matrix);
    PrintSkewDiagonal(n, matrix);

    return 0;
}
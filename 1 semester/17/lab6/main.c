#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 9
#define N 10

int matrix[M][N] =
{
    {-83, -71, -43,  -7,  -7,  -7,  -7,  58,  69,  92}, //sorted
    {-94, -89, -81, -64, -62, -62,  15,  15,  15,  47}, //sorted
    { 97,  69,  59,  49,  49,  49, -43, -45, -70, -72}, //reverse-sorted
    { 89,  28,  26,  25,   8,   5, -20, -87, -87, -87}, //reverse-sorted
    {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
    { 11,  11,  11,  11,  11,  11,  11,  11,  11,  11},
    { 17,  17,  17,  17,  17, -67, -67, -67, -67, -67}
};

int RandomRange(const int min, const int max) {
    return rand() % (max - min + 1) + min;
}

void FillRandom(const int startRow) {
    for (int i = startRow; i < M; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = RandomRange(-100, 100);
        }
    }
}

void PrintMatrix() {
    printf("\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void MatrixShellSort() {
    for (int i = 0; i < M; i++) {
        int k;
        int T;

        for (int d = 4; d >= 1; d /= 2) {
            for (int j = 0; j < N; j++) {
                for (k = j, T = matrix[i][j]; k >= d && matrix[i][k - d] > T; k -= d) {
                    matrix[i][k] = matrix[i][k - d];
                }
                matrix[i][k] = T;
            }
        }
    }
}

int main(void) {
    srand(time(nullptr));
    FillRandom(7);

    printf("Initial matrix");
    PrintMatrix();
    MatrixShellSort();
    printf("Sorted matrix");
    PrintMatrix();

    return 0;
}
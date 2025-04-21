#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

    srand(time(0));

    int m, n; //m rows and n columns
    printf("enter amount of rows and columns: ");
    scanf("%d %d", &m, &n);
    float matrix[m][n];

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0;
        }
    }

    printf("\nmatrix:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%7.3f ", matrix[i][j]);
        }
        printf("\n");
    }

    float max_value = matrix[0][0];
    int result_row, result_column;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if(matrix[i][j] >= max_value) {
                max_value = matrix[i][j];
                result_column = j;
                result_row = i;
            }
        }
    }

    printf("the largest last element: %.3f", max_value);
    printf("\n(row, column): (%d, %d)", result_row, result_column);

    return 0;
}

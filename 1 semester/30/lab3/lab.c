#include <stdio.h>

int main() {
    int n = 0;
    int m = 0;

    // m рядків n стовпців
    printf("Type Matrix[row][column]: ");
    scanf("%d %d", &m, &n);
    float matrix[m][n];

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%f", &matrix[i][j]);
        }
    }

    printf("\n");
    float min = matrix[0][0];
    int minRow = 0;
    int minColumn = 0;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%8.3f", matrix[i][j]);
            if (matrix[i][j] <= min) {
                min = matrix[i][j];
                minRow = i;
                minColumn = j;
            }
        }
        printf("\n");
    }

    // Виведення результату
    printf("\nMinimum value: %8.3f. Row %d, Column %d.\n", min, minRow, minColumn);

    return 0;
}

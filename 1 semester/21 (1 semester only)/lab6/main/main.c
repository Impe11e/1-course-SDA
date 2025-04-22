#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{

    srand(time(0));

    int m, n; //m rows and n columns
    printf("enter amount of rows and columns: ");
    scanf("%d %d", &m, &n);

    int matrix[m][n];

    int generate_randomly = 1;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 && j % 2 == 0) {
                if(generate_randomly) {
                    matrix[i][j] = rand() % 40 - 20;
                } else {
                    printf("enter element matrix[%d][%d]: ", i, j);
                    scanf("%d", &matrix[i][j]);
                }
            } else {
                matrix[i][j] = 0;
            }

        }
    }

    printf("\nmatrix:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 && j % 2 == 0) {
                printf("\x1b[31m%5d\x1b[0m", matrix[i][j]);
            } else {
                printf("%5d", matrix[i][j]);
            }
        }
        printf("\n");
    }

    //sort

    int flag = 1;
    int temp;

    while(flag) {
        flag = 0;
        for (int i = 0; i + 2 < n; i += 2) {
            if (matrix[0][i] > matrix[0][i + 2]) {
                temp = matrix[0][i];
                matrix[0][i] = matrix[0][i + 2];
                matrix[0][i + 2] = temp;
                flag = 1;
            }
        }
    }

    //result output
    printf("\nsorted matrix:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 && j % 2 == 0) {
                printf("\x1b[31m%5d\x1b[0m", matrix[i][j]);
            } else {
                printf("%5d", matrix[i][j]);
            }
        }
        printf("\n");
    }

    return 0;
}

#include <stdio.h>

int main()
{
    int m, n, min, T;
    printf("Enter the number of rows (m) and columns (n) (m,n): \n");
    scanf("%d,%d", &m, &n);

    int matrix[m][n];
    int last_row = m - 1;

    printf("Enter elements of the matrix: \n");

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }

    printf("Your matrix: \n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++)
    {
        if (i % 2 == 0)
        {
            min = i;
            for (int j = i + 1; j < n; j++)
            {
                if (j % 2 == 0 && matrix[last_row][j] < matrix[last_row][min])
                {
                    min = j;
                }
            }
            T = matrix[last_row][i];
            matrix[last_row][i] = matrix[last_row][min];
            matrix[last_row][min] = T;
        }
    }

    printf("Sorted matrix: \n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}

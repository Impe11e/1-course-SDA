#include <stdio.h>

int main()
{
    int m, n;
    printf("Enter the number of rows (m) and columns (n) (m,n): \n");
    scanf("%d,%d", &m, &n);
    double matrix[m][n];

    printf("Enter elements of the matrix: \n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%lf", &matrix[i][j]);
        }
    }

    printf("Your matrix: \n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%.3lf\t\t", matrix[i][j]);
        }
        printf("\n");
    }

    double x;
    printf("Enter x to find in your matrix: \n");
    scanf("%lf", &x);

    int found = 0;
    for (int j = 0; j < n; j++)
    {  int L = 0,
        R = m - 1;
        while (L <= R)
        {
            int mid = (L + R) / 2;
            if (matrix[mid][j] == x)
            {
                printf("Your x is located at (%d, %d)\n", mid, j);
                found = 1;
                break;
            }
            else
            {
                if (matrix[mid][j] > x)
                {
                    R = mid - 1;
                }
                else if (matrix[mid][j] < x)
                {
                    L = mid + 1;
                }
            }
        }

        if (found) break;
    }
    if (!found)
    {
    printf("Your x is not located at the matrix\n");
    }

return 0;
}


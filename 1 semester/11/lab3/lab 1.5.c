#include <stdio.h>

int main()
{
  int n;
  printf("Enter n of rows and columns: \n");
  scanf("%d", &n);
  int matrix[n][n];

  if(n<1) {
    printf("Incorrect value\n");
    return 1;
  }
  printf("Enter elements of matrix: \n");
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      scanf("%d", &matrix[i][j]);
    }
  }

  printf("Your matrix: \n");
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }

  int max = matrix[n-1][0];
  int min = matrix[n-1][0];
  int max_index = n-1;
  int min_index = n-1;

  for (int i = 0; i < n; i++) {
    int diag_element = matrix[n-i-1][i];
    if (diag_element > max)
    {
      max = diag_element;
      max_index = n-i-1;
    }
    if (diag_element <= min)
    {
      min = diag_element;
      min_index = n-i-1;
    }
  }

  printf("Your max element:\n%d\n", max);
  printf("Your min element:\n%d\n", min);

  int temp = matrix[max_index][n - max_index - 1];
  matrix[max_index][n - max_index - 1] = matrix[min_index][n - min_index - 1];
  matrix[min_index][n - min_index - 1] = temp;

  printf("Changed matrix:\n");
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
  return 0;
}

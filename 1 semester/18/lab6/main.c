#include <stdio.h>
#include <math.h>

#define print_line() printf("=========================================================================\n")

short get_number_length(double number) {
  return (number < 0 ? 1 : 0) + (short)log10(fabs(number)) + 1;
}

void init_matrix(const short rows, const short columns, double matrix[rows][columns], short max_lengths[columns]) {
  printf("Input elements of matrix:\n");
  print_line();

  for (short row = 0; row < rows; row++) {
    for (short column = 0; column < columns; column++) {
      if (row == 0) {
        max_lengths[column] = 0;
      }

      short current_length = 0;

      scanf("%lf", &matrix[row][column]);

      current_length = get_number_length(matrix[row][column]);

      if (current_length > max_lengths[column]) {
        max_lengths[column] = current_length;
      }
    }
  }
  print_line();
}

void print_matrix(const short rows, const short columns, double matrix[rows][columns], const short max_lengths[columns]) {
  for (short row = 0; row < rows; row++) {
    printf("| ");

    for (short column = 0; column < columns; column++) {
      short current_length = get_number_length(matrix[row][column]);
      for (short i = 0; i < max_lengths[column] - current_length; i++) {
        printf(" ");
      }

      printf("%lf ", matrix[row][column]);
    }

    printf("|\n");
  }
}

void quick_sort_matrix_column(
  const short start,
  const short end,
  const short column,
  const short rows,
  const short columns,
  double matrix[rows][columns]
) {
  if (start >= end || start < 0) {
    return;
  }

  short left = start, right = end;
  const double pivot = matrix[left][column];

  while (left < right) {
    while (matrix[right][column] < pivot && left < right) {
      right--;
    }

    if (left != right) {
      matrix[left][column] = matrix[right][column];
      left++;
    }

    while (matrix[left][column] > pivot && left < right) {
      left++;
    }

    if (left != right) {
      matrix[right][column] = matrix[left][column];
      right--;
    }
  }

  matrix[right][column] = pivot;

  quick_sort_matrix_column(start, right - 1, column, rows, columns, matrix);
  quick_sort_matrix_column(right + 1, end, column, rows, columns, matrix);
}

int main(void) {
  short rows_count, columns_count;

  print_line();
  printf("Input rows count:");
  scanf("%hu", &rows_count);
  printf("Input columns count:");
  scanf("%hu", &columns_count);
  print_line();

  if (rows_count <= 0 || columns_count <= 0) {
    printf("Sizes cannot be less then or equal 0");
    return -1;
  }

  double matrix[rows_count][columns_count];
  short max_lengths[columns_count];
  init_matrix(rows_count, columns_count, matrix, max_lengths);

  printf("Before sort:\n");
  print_matrix(rows_count, columns_count, matrix, max_lengths);

  for (short column = 0; column < columns_count; column++) {
    quick_sort_matrix_column(0, rows_count - 1, column, rows_count, columns_count, matrix);
  }

  print_line();
  printf("After sort:\n");
  print_matrix(rows_count, columns_count, matrix, max_lengths);

  return 0;
}
#include <stdio.h>

#define print_line() printf("=========================================================================\n")

enum INCLUDES {
  less,
  include,
  more
};

void init_matrix(const unsigned short rows, const unsigned short columns, double matrix[rows][columns]) {
  printf("Input elements of matrix:\n");
  print_line();

  for (unsigned short row = 0; row < rows; row++) {
    printf("Row %hu:\n", row);

    for (unsigned short column = 0; column < columns; column++) {
      printf("Input element (%hu; %hu):", row, column);
      scanf("%lf", &matrix[row][column]);
    }
    print_line();
  }
}

enum INCLUDES interval_includes(const double element, const double min, const double max) {
  enum INCLUDES result = include;

  if (element < min) {
    result = less;
  } else if (element > max) {
    result = more;
  }

  return result;
}

short binary_search(const double *array, const unsigned short length, const double min, const double max) {
  unsigned short left = 0, right = length - 1, middle;
  short result = -1;
  enum INCLUDES includes;

  while (left < right) {
    middle = left + (right - left) / 2;
    includes = interval_includes(array[middle], min, max);

    if (includes == more) {
      left = middle + 1;
    } else {
      right = middle;
    }
  }

  if (interval_includes(array[left], min, max) == include) {
    result = left;
  }

  return result;
}

int main(void) {
  unsigned short rows_count, columns_count;
  double min, max;

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
  init_matrix(rows_count, columns_count, matrix);

  printf("Input min target value:");
  scanf("%lf", &min);
  printf("Input max target value:");
  scanf("%lf", &max);
  print_line();

  unsigned short row;
  short column = -1;

  for (row = 0; row < rows_count; row++) {
    column = binary_search(matrix[row], columns_count, min, max);

    if (column != -1) {
      break;
    }
  }

  if (column == -1) {
    printf("Target element not found");
  } else {
    printf("Coords: (%d; %d)\n", row, column);
  }

  return 0;
}
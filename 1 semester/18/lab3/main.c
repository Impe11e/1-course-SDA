#include <stdio.h>

#define print_line() printf("=========================================================================\n")

struct coords {
  short row;
  short column;
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

short find_element_pos(const unsigned short rows, const unsigned short columns, double matrix[rows][columns], const double target_value, struct coords *pos) {
  printf("Start search...\n");
  print_line();

  for (unsigned short column = 0; column < rows; column++) {
    for (unsigned short row = 0; row < columns; row++) {
      if (matrix[row][column] == target_value) {
        pos->row = row;
        pos->column = column;
        return 0;
      }
    }
  }

  return -1;
}

int main(void) {
  unsigned short rows_count, columns_count;
  double target_value;

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

  printf("Input target value:");
  scanf("%lf", &target_value);
  print_line();

  struct coords pos;
  const short status = find_element_pos(rows_count, columns_count, matrix, target_value, &pos);

  switch (status) {
    case 0:
      printf("Coords: (%d; %d)\n", pos.row, pos.column);
      break;
    case -1:
      printf("Target element not found");
      break;
    default: ;
  }

  return status;
}
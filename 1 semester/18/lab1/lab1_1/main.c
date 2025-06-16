#include <stdio.h>

int main(void) {
  double x, result;

  printf("Enter value:");
  scanf("%lf", &x);

  if (x >= 0) {
    if (x < 7) {
      result = -6 * x * x + 8;
      printf("Result: %lf", result);
    } else if (x >= 11) {
      result = -1 * x * x * x / 7 + 10;
      printf("Result: %lf", result);
    } else {
      printf("No value");
    }
  } else if (x <= -10) {
    result = -1 * x * x * x / 7 + 10;
    printf("Result: %lf", result);
  } else {
    printf("No value");
  }

  return 0;
}

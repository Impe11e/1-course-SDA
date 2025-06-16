#include <stdio.h>
#include <math.h>

int main(void) {
  double result = 0, base, argument;
  int iterations;

  printf("Enter base: ");
  scanf("%lf", &base);
  printf("Enter argument: ");
  scanf("%lf", &argument);
  printf("Enter count of elements: ");
  scanf("%d", &iterations);

  const double init_numerator = argument * log(base);
  double numerator = 1;
  int denominator = 1;

  for (int i = 1; i <= iterations; i++) {
    denominator *= i;
    numerator *= init_numerator;

    result += numerator / denominator;
  }

  printf("Result: %lf", result);

  return 0;
}

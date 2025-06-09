#include <stdio.h>

double recursive_descent(unsigned int n, double arg, unsigned int i,
                         double current, double result) {
  if (i > n)
    return result;

  result += current;

  double mult = arg * arg / (4.0 * i * i - 2.0 * i);
  double next = current * mult;

  return recursive_descent(n, arg, i + 1, next, result);
}

int main() {
  double arg;
  unsigned int count;
  printf("Input argument: ");
  scanf("%lf", &arg);

  printf("Input count of iterations: ");
  scanf("%d", &count);

  double result = recursive_descent(count, arg, 1, 1, 0);

  printf("%lf\n", result);

  return 0;
}

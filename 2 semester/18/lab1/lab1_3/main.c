#include <stdio.h>

double recursive_mixed(unsigned int n, double arg, int i, double current) {
  if (i == n)
    return current;

  double mult = arg * arg / (4.0 * i * i - 2.0 * i);
  double next = current * mult;

  return current + recursive_mixed(n, arg, i + 1, next);
}

int main() {
  double arg;
  unsigned int count;

  printf("Input argument: ");
  scanf("%lf", &arg);

  printf("Input count of iterations: ");
  scanf("%d", &count);

  double result = recursive_mixed(count, arg, 1, 1);

  printf("%lf\n", result);

  return 0;
}

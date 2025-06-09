#include <stdio.h>

double loop(unsigned int n, double arg) {
  double current = 1;
  double result = current;

  for (int i = 1; i < n; i++) {
    double mult = arg * arg / (4.0 * i * i - 2.0 * i);

    current = current * mult;
    result += current;
  }

  return result;
}

int main() {
  double arg;
  unsigned int count;

  printf("Input argument: ");
  scanf("%lf", &arg);

  printf("Input count of iterations: ");
  scanf("%d", &count);

  double result = loop(count, arg);

  printf("%lf\n", result);

  return 0;
}

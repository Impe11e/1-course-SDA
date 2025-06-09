#include <stdio.h>

double recursive_ascent(unsigned int n, double arg, unsigned int i) {
  int start = 1;

  if (i == n)
    return start;

  double mult = arg * arg / (4.0 * i * i - 2.0 * i);

  return start + mult * recursive_ascent(n, arg, i + 1);
}

int main() {
  double arg;
  unsigned int count;

  printf("Input argument: ");
  scanf("%lf", &arg);

  printf("Input count of iterations: ");
  scanf("%d", &count);

  double result = recursive_ascent(count, arg, 1);

  printf("%lf\n", result);

  return 0;
}

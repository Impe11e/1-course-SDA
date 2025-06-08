#include <stdio.h>

double teylor(double x, unsigned int n, unsigned int i, double F)
{
    if (i > n)
        return 0;

    if (i == 1)
    {
        F = x - 1;
    }
    else
    {
        F = -F * (x - 1) * (i - 1) / i;
    }

    return F + teylor(x, n, i + 1, F);
}

int main()
{
    double x, res;
    unsigned int n;

    printf("enter x: ");
    scanf("%lf", &x);
    printf("enter n: ");
    scanf("%u", &n);

    res = teylor(x, n, 1, 0);
    printf("Result: %lf\n", res);
}
// mix

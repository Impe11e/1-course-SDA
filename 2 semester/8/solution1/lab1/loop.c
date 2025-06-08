#include <stdio.h>

int main()
{
    double F, prevF, x;
    double sum = 0;
    unsigned int i, n;

    printf("enter x: ");
    scanf("%lf", &x);
    printf("enter n: ");
    scanf("%u", &n);

    for (i = 1; i <= n; i++)
    {
        if (i == 1)
        {
            F = x - 1;
        }
        else
        {
            F = -prevF * (x - 1) * (i - 1) / i;
        }
        sum += F;
        prevF = F;
    }

    printf("Result: %lf\n", sum);
    return 0;
}

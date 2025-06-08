#include <stdio.h>
#include <math.h>

int main ()
{
    int n, i, ct;
    ct = 0;
    double S,P;
    S = 0;
    P = 1;
    printf("Enter n: \n");
    scanf("%d", &n);
    ct+=2; // S=0, P=1
    if (n > 0)
    {
        for (i = 1; i <= n; i++)
        {
            P *= i - sin(i);
            S += (i + cos(i)) / P;
            ct+= 10; // <=, ++, *=, -, sin(i), +=, +, cos(i), / , jmp
        }
        printf("Your result = %.7f\n", S);
        ct++; // i=1
    }
    else
    {
        printf("No value for n\n");
    }
    printf("Operations = %d\n", ct);
    return 0;
}


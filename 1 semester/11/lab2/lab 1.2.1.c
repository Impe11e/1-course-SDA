#include <stdio.h>
#include <math.h>
int main ()
{
    int n, i, j, ct;
    ct = 0;
    double S,P;
    S = 0;
    printf("Enter n: \n");
    scanf("%d", &n);
    ct++; // S=0
    if (n > 0)
    {
        for (i = 1; i <= n; i++)
        {
            P = 1;
            for (j = 1; j <= i; j++)
            {
                P *= j - sin(j);
                ct+=6; // <=, j++, *=, -, sin(j), jmp
            }
            S += (i + cos(i)) / P;
            ct+=9; // <=, ++, +=, +, /, cos(i), P=1, j=1, jmp
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

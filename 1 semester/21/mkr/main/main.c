#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main()
{
    int n;
    double a, x;
    printf("enter x:\n");
    scanf("%lf", &x);
    printf("enter n:\n");
    scanf("%d", &n);
    printf("enter a:\n");
    scanf("%lf", &a);
    double numerator = 1;
    int factorial = 1;
    double res = 0;
    double num = log(a);
    if (n >= 1 && a > 0) {
        for(int i = 1; i <= n; i++){
            factorial *= i;
            numerator *= x * num;
            res += numerator/factorial;
        }
        printf("res = %.7lf", res);
    } else {
        printf("inappropriate data");
    }
    return 0;
}

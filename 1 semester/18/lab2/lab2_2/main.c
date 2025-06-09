#include <stdio.h>
#include <math.h>

int main(void) {
    int n;
    double product = 1.0, sum = 0.0;

    printf("Enter count of product elements: ");
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        sum += i + sin(i);
        product *= sum / (i * i + 1);
    }

    printf("Product: %.7lf\n", product);

    return 0;
}
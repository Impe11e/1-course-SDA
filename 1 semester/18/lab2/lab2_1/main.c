#include <stdio.h>
#include <math.h>

int main(void) {
    int n;
    double product = 1.0;

    printf("Enter count of product elements: ");
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        double sum = 0.0;

        for (int j = 1; j <= i; j++) {
            sum += j + sin(j);
        }

        product *= sum / (i * i + 1);
    }

    printf("Product: %.7lf\n", product);

    return 0;
}
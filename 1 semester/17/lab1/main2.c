#include <stdio.h>

int main(void) {
    double x;
    double y;

    printf("\nEnter x: \n");
    scanf("%lf", &x);

    if (x >= 0 && (x <= 8 || x >= 16)) {
        y = -3.0 * x * x / 5.0 + 9.0;
        printf("y = %.4lf", y);
    } else if (x < -1) {
        y = 15 * x - 2;
        printf("y = %.4lf", y);
    } else {
        printf("x doesn't belong to the given intervals");
    }

    return 0;
}
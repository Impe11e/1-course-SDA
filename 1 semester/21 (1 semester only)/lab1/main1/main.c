#include <stdio.h>
#include <stdlib.h>

    int main()
{
    float x;
    float y;
    printf("Enter value of x: ");

    if (scanf("%f", &x) == 1) {
        if (x >= -49) {
            if (x < -10) {
                y = 10 * x * x * x + 7 * x / 5 + 2;
                printf("result: %.1f\n", y);
            }
            else {
                if (x > 0) {
                    if (x <= 10) {
                        y = 10 * x * x * x + 7 * x / 5 + 2;
                        printf("result: %.1f\n", y);
                    }
                    else {
                        if (x > 20) {
                            y = -1 * x + 9;
                            printf("result: %.1f\n", y);
                        }
                        else {
                            printf("y is undefined for that x\n");
                        }
                    }
                }
                else {
                    printf("y is undefined for that x\n");
                }
            }
        }
        else {
            printf("y is undefined for that x\n");
        }
    }
    else {
        printf("x is not a number.\n");
    }

    return 0;
}

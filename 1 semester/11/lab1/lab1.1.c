#include <stdio.h>

int main()
{
    float x, y;
    printf("input x: ");
    scanf("%f", & x);

    // x>20
    if (x > 20)
    {
        y = -x + 9;
        printf("your y(%.2f) = %.2f\n", x, y);
    }
    // x = [-49,-10)
    else if (x >= -49)
    {
        if (x < -10)
        {
            y = 10 * x * x * x + (7 * x) / 5 + 2;
            printf("your y(%.2f) = %.2f\n", x, y);
        }
        // x = (0,10]
        else if (x > 0)
        {
            if (x <= 10)
            {
                y = 10 * x * x * x + (7 * x) / 5 + 2;
                printf("your y(%.2f) = %.2f\n", x, y);
            }
            else
            {
                printf("no such value\n");
            }
        }
        else
        {
            printf("no such value\n");
        }
    }
    else
    {
        printf("no such value\n");
    }
    return 0;
}
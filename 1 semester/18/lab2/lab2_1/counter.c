#include <stdio.h>
#include <math.h>

struct counter {
    int assignments;
    int comperisons;
    int arithmetics;
    int jumps;
    int trigonometric;
};

void init_counter(struct counter *c) {
    c->assignments = 0;
    c->comperisons = 0;
    c->arithmetics = 0;
    c->jumps = 0;
    c->trigonometric = 0;
}

int sum_counter(struct counter *c) {
    return c->assignments + c->comperisons + c->arithmetics + c->jumps + c->trigonometric;
}

int main(void) {
    struct counter c;
    init_counter(&c);

    int n;
    double product = 1.0;
    c.assignments++; // product assignment

    printf("Enter count of product elements: ");
    scanf("%d", &n);
    c.assignments++; // n assignment

    c.assignments++; // i assignment
    for (int i = 1; i <= n; i++) {
        c.comperisons++; // i <= n

        double sum = 0.0;
        c.assignments++; // sum assignment

        c.assignments++; // j assignment
        for (int j = 1; j <= i; j++) {
            c.comperisons++; // j <= i

            sum += j + sin(j);
            c.trigonometric++; // calculate sin
            c.arithmetics++; // j + sin(j)
            c.assignments++; // added to sum

            c.arithmetics++; // j++
            c.jumps++;
        }

        product *= sum / (i * i + 1);
        c.arithmetics += 3; // multiplication, addition and division
        c.assignments++; //multiplied to product

        c.arithmetics++; // i++
        c.jumps++;
    }

    printf("Product: %.7lf\n", product);
    printf("Operations count: %d", sum_counter(&c));

    return 0;
}
#include <stdio.h>
#include <math.h>

int main() {
    int ct = 0;
    int n;
    double sum = 0;
    double product = 1;

    ct += 3; //n, sum, product

    printf("Type n: ");
    scanf("%d", &n);
    for(int i=1; i <= n; i++) {
        sum = sum + sin(i); 
        
        product = product * sum /( cos(i) + 1 );
        
        ct += 9; // <= | ++ | + | sin | * | / | cos | + | jmp
    }

    ct += 1;
    printf("\nSum: %.7f\n", sum);  
    printf("\nProduct: %.7f\n", product);  
    printf("\n Iterations: %d", ct);  
    return 0;
}

#include <stdio.h>
#include <math.h>

int main() {
    int ct = 0;
    int n;
    double sum = 0;
    double product = 1;
    
    
    ct += 3; // int n, sum, product
    printf("Type n: ");
    scanf("%d", &n);
    for(int i=1; i <= n; i++) {
        
        sum = 0;
        // =0, int j
        
        for (int j = 1; j <= i; j++) {
            sum = sum + sin(j); 
            
            ct += 5; // <= | ++ | sin | + | jmp 
        }
        
        product = product * sum /( cos(i) + 1 );
        
        ct += 9; // <= | ++ | = | int j | * | / | cos | + | jmp
    }
    
    ct += 1; // int i;
    
    printf("\nSum: %.7f\n", sum);  
    printf("\nProduct: %.7f\n", product);  
    printf("\nIterations: %d", ct);  
    return 0;
}

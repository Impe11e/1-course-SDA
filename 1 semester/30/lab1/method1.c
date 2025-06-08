#include <stdio.h>
int main() {
   
   float x;
   float y;
   int y_is_set = 0;
   printf("Enter x: \n");
   scanf("%f", &x);

   if(x >= 8) {
        if(x < 23) {
            y = -5 * x * x * x + 10;
            y_is_set = 1; 
        } else {
            printf("Your x is off the range.");
        }
   } else if(x < -19) {
        y = 2 * x * x * x + 8 * x * x;
        y_is_set = 1; 
   } else if(x > -3) {
        if(x <= 0) {
            y = 2 * x * x * x + 8 * x * x;
            y_is_set = 1; 
        } else {
            printf("Your x is off the range.");
        }
    } else {
        printf("Your x: is off the range.");
    }

    
   if(y_is_set) {
        printf("\nYour x: %.3f.\nYour y: %.3f.", x, y);
   } else {
        printf("\n%.3f is not working. Try again.", x);
   }

   return 0;
}

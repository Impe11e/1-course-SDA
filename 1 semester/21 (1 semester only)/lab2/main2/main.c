#include <stdio.h>
#include <math.h>

int main() {
   int n;
   double product = 1;
   double sum = 0;
   int powers = 1;
   int counter = 0;

   printf("enter n: ");
   scanf("%d", &n);

   counter+=4; //n, product, sum, powers initialization

   for (int i = 1; i <= n; i++) { //2 comparison, increment
      product *= ((i + 2)/10.0); //3 sum, division, multiplication
      powers *= 2; //1 multiplication
      sum += product / (powers * i); //3 sum, division, multiplication
      counter+=10; //9+jump
   }

   counter+=3;//3 for extra increment, extra comparison, initialization of i

   printf("sum: %.7lf\n", sum);
   printf("amount of operations: %d\n", counter);
   return 0;
}

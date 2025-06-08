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

   for (int i = 1; i <= n; i++) {//2 comparison, increment
      product = 1; //1 assignment
      for (int j = 1; j <= i; j++) { //2 comparison, increment
         product *= ((j + 2)/10.0); //3 sum, division, multiplication
         counter += 6; //5+1 jump to the start of the inner for-loop
      }
      powers *= 2;//1 multiplication
      sum += product / (powers * i);//3 sum, division, multiplication
      counter += 11; //7+1 jump to the start of the outer for-loop+3 for each extra increment, extra comparison, initialization of j
   }

   counter+=3;//3 for extra increment, comparison, i initialization


   printf("sum: %.7lf\n", sum);
   printf("amount of operations: %d\n", counter);
   return 0;
}

#include <stdio.h>
#include <math.h>

int main (){
int n,i,c;
double P,S;

printf("Enter n to calculate\n");
printf("n= ");
scanf("%i",&n);
c=0;

S=0;P=1;
for (int i=1;i<=n;i++){
 S+= i * sin(i) + i;
 P*=(i * sqrt(i)) / S;
 c+=11;
 }
c+=3;

printf("result is: %.7f  \n", P);
printf("counter: %i", c);
}

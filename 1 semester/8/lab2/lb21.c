#include <stdio.h>
#include <math.h>

int main (){
int n,i,j,c;
double P,S;

printf("Enter n to calculate\n");
printf("n= ");
scanf("%i",&n);
c=0;

S=0;P=1;
 for (int i=1;i<=n;i++){
  for (int j=1;j<=i;j++){
  S+=(j * sin(j) + j);
  c+=7;
  }
 P*=(i * sqrt(i) / S);
 S=0;
 c+=9;
 }
c+=3;

printf("result is: %.7f  \n", P);
printf("counter: %i", c);
}

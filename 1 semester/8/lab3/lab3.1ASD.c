#include <stdio.h>
#include <math.h>
#define n 9  //n=...

int main (){
int t,i1,i2;
float lastPlus,firstMinus;
float A[n][n] = {
             {1.7,8,-3,14,7,-1,6,-9,-5},
             {7,2,-6,5,12,3,-4,-7, 10},
             {-2,15,-5.5,3.33,9,-5,13,7,8},
             {4.98,-6,-2,8,3.789, -9, 12, -7,15},
             {-5,14,6,1,6.4, -3, 11.8,9,-2},
             {-1,4,13,5,9,-13,2,-8.9,10},
             {14.12,12.3, -5, -3,7,8,3,-1,11},
             {11,7,8,15,-2,4,-3.89,9.23,-4},
             {-9,-4,10,1, 6, -7, 13, 5, -1.1}};

printf("matrix A:\n\n");
for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%5.2f ", A[i][j]);
        }
        printf("\n\n"); //
    }

for (i1 = 0; A[i1][i1]>=0 && i1<n; i1++);
if (A[i1][i1]<0){
    firstMinus = A[i1][i1];
    printf("first element<0 on main diagonal: %.2f\n", A[i1][i1]);}
else{
    printf("there is no element<0\n");}

for (i2 = 1; A[n-i2][n-i2]<=0 && i2<n; i2++);
if (A[n-i2][n-i2]>0){
    lastPlus=A[n-i2][n-i2];
    printf("last element>0 on main diagonal: %.2f\n\n", A[n-i2][n-i2]);}
else{
    printf("there is no element>0\n\n");}

if (A[i1][i1]<0 && A[n-i2][n-i2]>0){
A[i1][i1] = lastPlus;
A[n-i2][n-i2] = firstMinus;
printf("changed matrix A:\n\n");
for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%5.2f ", A[i][j]);
        }
        printf("\n\n"); //
    }
  }
}


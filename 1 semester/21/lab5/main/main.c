#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

    srand(time(0));

    int n;
    printf("enter amount of rows and columns: ");
    scanf("%d", &n);
    float matrix[n][n];


    //generation of matrix
    float random_number;
    float prev;
    int step = 5;

    for (int i = 0; i < n; i++) {
        float r = (float)rand()/RAND_MAX;
        random_number += r;
        float repeat_chance = (float)rand()/RAND_MAX;
        for (int j = 0; j < n; j++) {
            if (i != n - j - 1) {
                matrix[i][j] = 0;
            } else {
                if(i != 0) {
                    if (repeat_chance < 0.6 && repeat_chance > 0.3) {
                    matrix[i][j] = prev;
                    } else {
                    matrix[i][j] = random_number;
                    prev = matrix[i][j];
                    }
                } else {
                    matrix[i][j] = random_number;
                    prev = matrix[i][j];
                }
            }
        }
    }

    //matrix print
    printf("\nmatrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%8.3f ", matrix[i][j]);
        }
        printf("\n");
    }

    //binary search
    int left = 0;
    int right = n - 1;
    int res_index = -1;

    while (left <= right) {

        int mid = (right + left) / 2;

        if (matrix[mid][n - mid - 1] <= 5.0 && matrix[mid][n - mid - 1] >= 0.0) {
            res_index = mid;
            break;
        } else if (matrix[mid][n - mid - 1] > 5.0) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    //result output
    if (res_index != -1) {
        printf("\n(row, column): (%d, %d)\n", res_index, n - res_index - 1);
        printf("value: %.3f\n", matrix[res_index][n - res_index - 1]);
    } else {
        printf("\nno elements were found in the range [0, 5] on the secondary diagonal\n");
    }

    return 0;
}

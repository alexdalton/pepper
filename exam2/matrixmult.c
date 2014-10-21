#include <stdio.h>
#include <stdlib.h>

/* We will grade your code by changing these values
 * So test different matrice sizes by changing these */

#define DIM_N      12    // The n dimension (height of A and C)
#define DIM_M      13    // The m dimension (width of A and height of B)
#define DIM_P      14    // The p dimension (width of B and C)


/* Please do NOT change any of the given code */
int main(void)
{
    int matrix_a[DIM_M][DIM_N]; // First matrix to be multiplied
    int matrix_b[DIM_P][DIM_M]; // Second matrix to be multiplied
    int matrix_c[DIM_P][DIM_N]; // Output matrix of the multiplication

    // If you choose to use i and j variables note they are declared here
    int i, j;                     
    srand(12321);

    // Initialize and print matrix A
    printf("Matrix A: %d x %d\n", DIM_N, DIM_M);
    for (i = 0; i < DIM_N; i++)
    {
        for (j = 0; j < DIM_M; j++)
        {
            matrix_a[j][i] = rand() % 10;
            printf("%d   ", matrix_a[j][i]);
        }
        printf("\n");
    }

    // Initialize and print matrix B
    printf("Matrix B: %d x %d\n", DIM_M, DIM_P);
    for (i = 0; i < DIM_M; i++)
    {
        for (j = 0; j < DIM_P; j++)
        {
            matrix_b[j][i] = rand() % 10;
            printf("%d   ", matrix_b[j][i]);
        }
        printf("\n");
    }

    // Compute matrix multiplication and write to matrix_c
    // INSERT YOUR CODE HERE
    int row, col, sum, k;
    for (row = 0; row < DIM_N; row++)
    {
        for (col = 0; col < DIM_P; col++)
        {
            sum = 0;
            for(k = 0; k < DIM_M; k++)
            {
                sum += matrix_a[k][row] * matrix_b[col][k];
            }
            matrix_c[col][row] = sum;
        }

    }

    // Print matrix C
    printf("Matrix C: %d x %d\n", DIM_N, DIM_P);
    for (i = 0; i < DIM_N; i++)
    {
        for (j = 0; j < DIM_P; j++)
        {
            int value = matrix_c[j][i];
            int spaceCount = 4;
            while (value >= 10)
            {
                value /= 10;
                spaceCount -= 1;
            }
            printf("%d", matrix_c[j][i]);
            for(;spaceCount > 0; spaceCount--)
                printf(" ");
        }
        printf("\n");
    }

    return 0;
}


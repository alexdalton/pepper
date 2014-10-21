#include <stdio.h>
#include <stdlib.h>

/********* FUNCTION DEFINITIONS *********/
int** allocateMatrix(int width, int height);
void deallocateMatrix(int** matrix, int width);
void initializeMatrix(int** matrix, int width, int height);
void matrixMultiply(int** matrix_a, int** matrix_b, int** matrix_c, int n, int m, int p);
void printMatrix(int** matrix, char name, int width, int height);

int main(int argc, char* argv[])
{
    int n, m, p;
    char post[2];

    // Check for correct number of arguments
    if (argc < 4)
    {
        printf("Not enough arguments, must enter in matrix dimensions\n");
        printf("Usage: ./matrix n m p\n");
        return 1;
    }
    else if (argc > 4)
    {
        printf("Too many arguments\n");
        printf("Usage: ./matrix n m p\n");
        return 1;
    }

    // Get n, m, and p arguments
    if(1 != sscanf(argv[1], "%d%1s", &n, post) ||
       1 != sscanf(argv[2], "%d%1s", &m, post)  ||
       1 != sscanf(argv[3], "%d%1s", &p, post))
    {
        printf("Invalid arguments\n");
        printf("Usage: ./matrix n m p\n");
        return 1;
    }

    // allocate memory for matrices
    int ** matrix_a = allocateMatrix(m, n);
    int ** matrix_b = allocateMatrix(p, m);
    int ** matrix_c = allocateMatrix(p, n);

    // initialize random number generator and matrices with values
    srand(12321);   // please don't change this seed value
    initializeMatrix(matrix_a, m, n);
    initializeMatrix(matrix_b, p, m);

    // compute matrix multiplication
    matrixMultiply(matrix_a, matrix_b, matrix_c, n, m, p);

    printMatrix(matrix_a, 'A', m, n);
    printMatrix(matrix_b, 'B', p, m);
    printMatrix(matrix_c, 'C', p, n);

    // deallocate memory for matrices
    deallocateMatrix(matrix_a, m);
    deallocateMatrix(matrix_b, p);
    deallocateMatrix(matrix_c, p);

    return 0;
}

/*
 * FUNCTION:     matrixMultiply
 * INPUT:        matrix_a - the A matrix for the matrix multiplication
 *               matrix_b - the B matrix for the matrix multiplication
 *               matrix_c - the C matrix, this holds the result of A x B
 * SIDE EFFECTS: matrix_c is written to and holds the result of A x B
 * OUTPUT:       none
 */
void matrixMultiply(int** matrix_a, int** matrix_b, int** matrix_c, int n, int m, int p)
{
    int row, col, sum, i;
    for (row = 0; row < n; row++)
    {
        for (col = 0; col < p; col++)
        {
            sum = 0;
            for(i = 0; i < m; i++)
            {
                sum += matrix_a[i][row] * matrix_b[col][i];
            }
            matrix_c[col][row] = sum;
        }

    }
}

/*
 * FUNCTION:     printMatrix
 * INPUT:        matrix - the matrix to print
 *               name   - a character representing the name of the matrix
 *               width  - the width of the matrix
 *               height - the height of the matrix
 * SIDE EFFECTS: prints the matrix in a readable format
 * OUTPUT:       none
 */
void printMatrix(int** matrix, char name, int width, int height)
{
    int row, col;
    printf("Matrix %c: %d by %d\n", name, height, width);
    for (row = 0; row < height; row++)
    {
        for (col = 0; col < width; col++)
        {
            int value = matrix[col][row];
            int spaceCount = 5;
            while (value >= 10)
            {
                value /= 10;
                spaceCount -= 1;
            }
            printf("%d", matrix[col][row]);
            for(;spaceCount > 0; spaceCount--)
                printf(" ");
        }
        printf("\n");
    }
    printf("======================\n");
}

/* 
 * FUNCTION:     allocateMatrix
 * INPUT:        width  - width of matrix to allocate
 *               height - height of matrix to allocate
 * SIDE EFFECTS: allocates memory for a width x height matrix
 * OUPUT:        an int** (2D array). This is the matrix.
 */
int** allocateMatrix(int width, int height)
{
    int** matrix = (int**) malloc(width * sizeof(int*));
    int i;
    for (i = 0; i < width; i++)
    {
        matrix[i] = (int*) malloc(height * sizeof(int));
    }
    return matrix;
}

/*
 * FUNCTION:     initializeMatrix
 * INPUT:        matrix - 2D array to initialize with values
 *               width  - width of 2D array
 *               height - height of 2D array
 * SIDE EFFECTS: initializes 2D array with random values between 0 and 4999
 * OUPUT:        none
 */
void initializeMatrix(int** matrix, int width, int height)
{
   int i, j;
   for (i = 0; i < height; i++)
   {
       for (j = 0; j < width; j++)
       {
           matrix[j][i] = rand() % 10;
       }
   }
}

/*
 * FUNCTION:     deallocateMatrix
 * INPUT:        matrix - 2D array of integers
 *               width  - width of the matrix
 * SIDE EFFECTS: frees memory for the given matrix
 * OUTPUT:       none
 */
void deallocateMatrix(int** matrix, int width)
{
    int i;
    for (i = 0; i < width; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

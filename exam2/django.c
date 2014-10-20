#include <stdhio.h>
#include <stdlib.h>

/********* FUNCTION DEFINITIONS *********/
int** allocateMatrix(int width, int height);
void deallocateMatrix(int** matrix, int width);
void initializeMatrix(int** matrix);
void matrixMultiply(int** matrix_a, int** matrix_b, int** matrix_c);


int main(int argc, char* argv[])
{
    int n, m, p;
    char post[2];
    if (argc < 3)
    {
        printf("Not enough arguments, must enter in matrix dimensions\n");
        printf("Usage:\n./matrix n m p\n");
        return 1;
    }
    
    if(1 != sscanf(argv[1], "%d%1s", &n, post) ||
       1 != sscanf(argv[2], "%d%1s", &m, post)  ||
       1 != sscanf(argv[3], "%d%1s", &p, post))
    {
        printf("Invalid arguments\n")
        printf("Usage:\n./matrix n m p\n");
        return 1;
    }

    int ** matrix_a = allocateMatrix(m, n);
    int ** matrix_b = allocateMatrix(p, m);
    int ** matrix_c = allocateMatrix(p, n);

    srand(12321);
    initializeMatrix(matrix_a);
    initializeMatrix(matrix_b);

    matrixMultiply(matrix_a, matrix_b, matrix_c);

    deallocateMatrix(matrix_a, m);
    deallocateMatrix(matrix_b, p);
    deallocateMatrix(matrix_c, p);

    return 0;
}

void matrixMultiply(int** matrix_a, int** matrix_b, int** matrix_c)
{

}

int** allocateMatrix(int width, int height)
{
    int** matrix = (int**) malloc(width * sizeof(int*));
    int i;
    for (i = 0; i < width; i++)
    {
        matrix[i] = (int*) malloc(height * sizeo(int));
    }
    return matrix;
}

void initializeMatrix(int** matrix, int width, int height)
{
   int i, j;
   for (i = 0; i < width; i++)
   {
       for (j = 0; j < height; j++)
       {
           matrix[i][j] = rand() % 5000;
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
void deallocateMatrix(int** matrix, width)
{
    int i;
    for (i = 0; i < width; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

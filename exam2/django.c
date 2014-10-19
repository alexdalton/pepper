#include <stdhio.h>
#include <stdlib.h>

double** allocateMatrix(int width, int height);
void deallocateMatrix(double** matrix, int width);
void initializeMatrix(double** matrix);

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

    double ** matrix_a = allocateMatrix(m, n);
    double ** matrix_b = allocateMatrix(p, m);
    double ** matrix_c = allocateMatrix(p, n);

    initializeMatrix(matrix_a);
    initializeMatrix(matrix_b);

    matrixMultiply(matrix_a, matrix_b, matrix_c);

    deallocateMatrix(matrix_a, m);
    deallocateMatrix(matrix_b, p);
    deallocateMatrix(matrix_c, p);

    
    return 0;
}

double** allocateMatrix(int width, int height)
{
    double** matrix = (double**) malloc(width * sizeof(double*));
    int i;
    for (i = 0; i < width; i++)
    {
        matrix[i] = (double*) malloc(height * sizeof(double));
    }
    return matrix;
}

void initializeMatrix(double** matrix)
{
    
}

void deallocateMatrix(double** matrix, width)
{
    int i;
    for (i = 0; i < width; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

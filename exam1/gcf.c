#include <stdio.h>

// FUNCTION DECLARATIONS
void printGCF(int val1, int val2);


int main(void)
{
    int value1, value2;
    char inCheck;

    // Get two positive integers to find the GCF of
    printf("Enter two positive integers: ");
    if (scanf("%d%d%c", &value1, &value2, &inCheck) != 3 || inCheck != '\n' || value1 < 1 || value2 < 1)
    {
        printf("Invalid value\n");
        return -1;
    }

    // Find and print the GCF of value1 and value2
    printGCF(value1, value2);
    return 0;
}

/*
 * printGCF -- prints the greatest common factor of two positive integers
 * INPUTS: val1 -- the first integer
 *         val2 -- the second integer
 * OUTPUTS: none
 * SIDE EFFECTS: prints the greatest common factor
 * */
void printGCF(int val1, int val2)
{
    // INSERT YOUR CODE HERE
}

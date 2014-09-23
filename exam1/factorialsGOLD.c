#include <stdio.h>

// FUNCTION DECLARATIONS
void printFactorials(int value);


int main(void)
{
    int value;
    char inCheck;

    // Get positive integer to use to print first n factorials
    printf("Enter a positive integer: ");
    if (scanf("%d%c", &value, &inCheck) != 2 || inCheck != '\n' || value < 1 || value > 12)
    {
        printf("Invalid value\n");
        return -1;
    }

    // Print the factorials
    printFactorials(value);
    return 0;
}

/*
 * printFactorials -- prints all factorials less than or equal to the value
 * INPUTS: value -- the first n factorials to print
 * OUTPUTS: none
 * SIDE EFFECTS: prints the first x factorials where x is the value parameter
 *               (NOTE: output format must adhere strictly to specified format)
 */
void printFactorials(int value)
{
    int i, j;
    printf("1 = 1\n");
    for (i = 2; i <= value; i++)
    {
        unsigned int factorial = 1;
        printf("1 ");
        for(j = 2; j <= i; j++)
        {
            printf("* %d ", j);
            factorial *= j;
        }
        printf("= %d\n", factorial);
    }
}

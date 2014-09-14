#include <stdio.h>
#include "printBinary.h"

/********* FUNCTION DECLARATIONS *************/
void convert(int value, int key);

int main(void)
{
    int value, key;
    printf("Enter an integer: ");
    scanf("%d", &value);

    printf("0: Binary\n1: Octal\n2: Decimal\n3: Hex\n");
    printf("Enter conversion: ");
    scanf("%d", &key);

    convert(value, key);
    return 0;
}

/*
 * Converts a value to a different base representation and prints it
 * @param value The value to convert
 * @param key The key that indicates the conversion operation
 * @return none
 */
void convert(int value, int key)
{
    // INSERT YOUR CODE HERE
}


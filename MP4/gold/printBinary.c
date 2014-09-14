#include <stdio.h>

/* 
 * Prints a 32 bit integer in binary
 * @param value The integer to print in binary
 * @return none
 */
void printBinary(int value)
{
    unsigned char *b = (unsigned char*) &value;
    unsigned char byte;
    int i, j;
    for(i = 3; i >= 0; i--)
    {
        for(j = 0; j < 8; j++)
        {
            byte = b[i] & (1 << j);
            byte = byte >> j;
            printf("%u", byte);
        }
    }
    printf("\n");
}


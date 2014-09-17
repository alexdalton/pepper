#include <stdio.h>

/* 
 * Prints an integer in binary
 * @param value The integer to print in binary
 * @param size Size of an integer in bytes
 * @return none
 */
void printBinary(int value, int size)
{
    int i;
    for(i = 0; i < (size * 8); i++)
    {
        if (value & 0x80000000)
            printf("1");
        else
            printf("0");
        value <<= 1;
    }
    printf("\n");
}


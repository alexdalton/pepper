#include <stdio.h>

void convert(int value, int key);
void printBinary(int value);

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

void convert(int value, int key)
{
    switch (key)
    {
        case 0:
            printBinary(value);
            break;
        case 1:
            printf("%o\n", value);
            break;
        case 2:
            printf("%d\n", value);
            break;
        case 3:
            printf("0x%X\n", value);
            break;
        default:
            printf("Invalid option\n");
            break;
    }
}

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
